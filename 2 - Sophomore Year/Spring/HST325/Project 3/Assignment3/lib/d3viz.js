/* Alex Wellerstein's basic D3 Vizualization Template -- designed to make the creation of D3 vizualizations more modular */


var d3VizObj = {
	//holds data objects
	data: new Array(), //datasets
	maps: new Array(), //maps
	viz: new Array(), //visualizations
	controls: new Array(), //other things (filters, etc.)
	//hooks
	runHook: function(hook_name, hook_var) { //runs a hook function
		if(typeof d3VizObj.hooks[hook_name]!=="undefined") {
			if(debug) console.log("Hook: "+hook_name+" ["+d3VizObj.hooks[hook_name].length+"]");
			if(d3VizObj.hooks[hook_name].length>0) {
				for(var i in d3VizObj.hooks[hook_name]) {
					if(typeof d3VizObj.hooks[hook_name][i] == "function") d3VizObj.hooks[hook_name][i](hook_var);
				}			
			}
			//console.log(d3VizObj.hooks[hook_name]);
		} else {
			if(debug) console.log("Hook: "+hook_name+" [0]");
		}
	},
	addHook: function(hook_name, func) { //add a hook function
		if(typeof d3VizObj.hooks[hook_name]=="undefined") d3VizObj.hooks[hook_name] = [];
		d3VizObj.hooks[hook_name].push(func);
	},
	hooks: new Array(), //holder of hooks
	map_loaded: 0, //counts maps as they load
	data_loaded: 0, //counts datasets as they load
	datas_hook_run: 0, //records whether run_after_datas_loaded has run already 
	maps_hook_run: 0, //records whether run_after_maps_loaded has run already
	is_loaded: function(obj) {
		if(obj.type=="map") this.map_loaded++;
		if(obj.type=="data") this.data_loaded++;
		if((this.map_loaded>=d3VizObj.maps.length)&&(!this.maps_hook_run)) {
			d3VizObj.runHook("run_after_maps_loaded");
			this.maps_hook_run = true;
		}
		if((this.data_loaded>=d3VizObj.data.length)&&(!this.datas_hook_run)) {
			d3VizObj.runHook("run_after_datas_loaded");
			this.datas_hook_run = true;
		}
		if((this.map_loaded>=d3VizObj.maps.length)&&(this.data_loaded>=d3VizObj.data.length)) {
			d3VizObj.runHook("run_after_data_and_map_loaded");
			d3VizObj.runHook("run_after_everything");
		}
	},
	load: function() { //two for one -- loads maps and data in one go
		d3VizObj.loadMaps();
		d3VizObj.loadData();
	},
	loadMaps: function() { //load all the maps
		d3VizObj.runHook("run_before_maps_loaded");
		if(debug) console.log("Loading map(s): "+this.maps.length);
		if(this.maps.length) {
			for(var i in this.maps) {
				d3VizObj.runHook("run_before_map_loaded",this.maps[i]);
				if(debug) console.log("Loading map "+i);
				this.maps[i].load();
			}
		}
	},
	loadData: function() { //load all the data
		d3VizObj.runHook("run_before_datas_loaded");
		if(debug) console.log("Loading dataset(s): "+this.data.length);
		if(this.data.length) {
			for(var i in this.data) {
				d3VizObj.runHook("run_before_data_loaded",this.data[i]);
				if(debug) console.log("Loading dataset "+i);
				this.data[i].load();
			}
		}		
	},
};

function d3Viz(constructor) { //basic constructor for data, controls, etc.
	this.constructor = constructor;
	this.loadOptions = function(options) { //moves options into main scope
		for(var i in options) {
			this[i] = options[i];
		}
	}
}

function d3Data(options) {
	var obj = this;
	obj.loadOptions(options);

	this.type = "data";

	d3VizObj.data.push(this);
	this.id = d3VizObj.data.length-1;
	
	this.load = function () {
		if(obj.csv) {
				if(debug) console.log("Trying to load CSV data from "+obj.csv);
				d3.csv(obj.csv, function(datarows) {
					obj.data = new Array();
					if(datarows == null) alert("Could not load "+obj.csv+" - check that file path is valid and you are using a browser that allows for file requests");
					var i = 0; //just a counter
					datarows.forEach(function (d) {
						d.i = parseInt(i); //keep track of row number
						if(debug&&debug_verbose) console.log("Parsing row "+i);
						d3VizObj.runHook("run_on_each_data_row",{d,i,obj});
						if(d) { //if object still exists 
							obj.data.push(d);
							i++;
						}
					})
					d3VizObj.runHook("run_after_data_loaded",obj);
					d3VizObj.is_loaded(obj);
				})

		} else {
			if(debug) console.log("No file specified!"); //maybe someday add tsv support
			d3VizObj.is_loaded(this);
		}	
	}	
}
d3Data.prototype = new d3Viz(d3Data);

//SVG map -- JSON file
function d3SVGMap(options) {
	var obj = this;
	obj.loadOptions(options);

	obj.type = "map";
	obj.maptype = "SVG"; 
	obj.zoom_factor = 1; //keeps track of zooming for SVG elements

	obj.projection = d3.geo[obj.projection_name](); //set projection
	if(obj.projection_rotate) obj.projection.rotate(obj.projection_rotate) //rotates the world
	if(obj.projection_scale) obj.projection.scale(obj.projection_scale) 			 //sets the zoom factor 
	if(obj.projection_translate) obj.projection.translate(obj.projection_translate); //moves the map 

	d3VizObj.maps.push(obj); obj.id = d3VizObj.maps.length-1;

	//resizes map when window resizes
	this.updateWindow = function (map) { 
		var w = window;
		var window_width = w.innerWidth || e.clientWidth || g.clientWidth;
		var window_height = w.innerHeight|| e.clientHeight|| g.clientHeight;
		map.svg.attr("height", window_height);	
	}

	//loads map
	this.load = function() {
		//create a path to manipulate
		obj.path = d3.geo.path().projection(this.projection);

		//create a svg object, add to div
		obj.svg = d3.selectAll(obj.div).append('svg')
				.attr('width',obj.width)
				.attr('height',obj.height)
				.attr("viewBox","0 0 "+obj.width+" "+obj.height) //this last line makes it resize along with the browser window
		
		//make it resize with window -- can be override by setting noUpdate to true
		if(!obj.noUpdate) {
			window.onresize = function() { obj.updateWindow(obj) }
		}

		//creates various object groups we can later manipulate
		//you should not change these base three -- stage, landforms, and captions -- but you can add others
		this.addGroup("stage",map.svg); //a basic group that other things are attached to -- useful for zooming
		this.addGroup("landforms",map.stage); //where the base map lives
		this.addGroup("captions",map.stage); //where captions live
		
		//run an onload if it exists
		if(typeof obj.onload == "function") obj.onload();
		
		//if we have map file
		if(obj.mapfile) {
			//load the json...
			d3.json(obj.mapfile, function(error, world) {
				if(debug) console.log("Loading mapfile ("+(obj.mapfile)+")");
				//this "switch" just makes this compatible with the two main types of map files
				switch(world.type) {
					case "FeatureCollection": 
					obj.landforms.append("g")
						.selectAll(".land_boundaries")
						.data(world.features)
						.enter().append("path")
						.attr("class", function(d){ return d.properties.name; })
						.attr("id",function(d,i) { return "map_"+obj.id+"_"+i; })
						.classed("boundaries",true)
						.attr("d", obj.path)
						;
					break;
					case "Topology":
						obj.addGroup("land",map.landforms,".land");
						obj.addGroup("boundaries",map.landforms,".boundaries");
						//try to load all the map objects
						var xx = []; 
						for(x in world.objects) xx.push(x);
						for(y in xx) {
							x = xx[y];
							if(world.objects[x].type=="MultiPolygon") {
							  if(debug) console.log("Loading map object: "+x);
							  obj.land.append("path")
								  .datum(topojson.feature(world, world.objects[x]))
								  .classed("map_"+x,true)
								  .classed("map",true)
								  .classed("map_polygon",true)
								  .attr("d", obj.path)
								  .attr("id","map_polygon_"+obj.id+"_"+x)
								  ;	
							} else if(world.objects[x].type=="GeometryCollection") {
							  if(debug) console.log("Loading map object: "+x);
							  obj.boundaries.selectAll(".boundaries")
								  .data(topojson.feature(world, world.objects[x]).features)
								  .enter()
								  .append("path")
								  .each(function(d,i) {
									if(typeof d.id!="undefined") { 
										var did = String(d.id).replace(" ","_");
										if(debug_verbose&&debug) console.log("Identified map item id_"+did);
										d3.select(this).attr("id","id_"+did);
									}
									if(typeof d.properties!="undefined") {
										if(typeof d.properties.id !="undefined") {
											var did = String(d.properties.id).replace(" ","_");
											if(debug_verbose&&debug) console.log("Identified map item id_"+did);
											d3.select(this).attr("id","id_"+did);
										}
										if(typeof map_properties!="undefined") {
											for(var ii in map_properties) {
												if(typeof d.properties[map_properties[ii]] !="undefined") {
													var propname = String(map_properties[ii]).replace(" ","_");
													var propval_id = String(d.properties[map_properties[ii]]).replace(" ","_")
													d3.select(this).classed("prop_"+propname+"_"+propval_id,true);
													if(debug_verbose&&debug) console.log("Identified map item property prop_"+propname+"_"+propval_id);

												}
											}
										}						  	
									}
									if(d3.select(this).attr("id")<="") {
										d3.select(this).attr("id","map_"+obj.id+"_"+i);
										if(debug_verbose&&debug) console.log("Labeled map item as "+"map_"+obj.id+"_"+i);
									}
								  })
								  .classed("map_"+x,true)
								  .classed("map",true)
								  .classed("boundary",true)
								  .attr("d", obj.path)
								  ;	
							} else {
								if(debug) console.log("Unknown map object: "+world.objects[x]);
							}
					}
					 break;
				}
				if(debug) console.log("Mapfile loaded ("+obj.mapfile+")");
				//run hook
				d3VizObj.runHook("run_after_map_loaded",obj);
				d3VizObj.is_loaded(obj);
			});
		} else {
			//no map file.. move on
			if(debug) console.log("Mapfile not loaded -- no mapfile defined!");
			d3VizObj.runHook("run_after_map_loaded");
			d3VizObj.is_loaded(this);
		} 
	}
	//adds a svg group
	this.addGroup = function(id, parent, label) {
		if(typeof label=="undefined") {
			this[id] = parent.append("g").attr("id",id);
		} else {
			if(label[0]=="#") {
				this[id] = parent.append("g").attr("id",label.substr(1,label.length));			
			} else if (label[0]==".") { 
				this[id] = parent.append("g").attr("class",label.substr(1,label.length));			
			}
		}
		return this[id];
	}
}
d3SVGMap.prototype = new d3Viz(d3SVGMap);

//Google Map -- 
function d3GMap(options) {
	var obj = this;
	obj.loadOptions(options);
	obj.type = "d3GMap";

	
	//runs when the overlay draws
	this.overlayDraw = function() {
			//reposition the data
			if(debug) console.log("Positioning data overlay");
			obj.projection = this.getProjection();
			//mapcenter records the center of the map the last time the projection changed
			//from this it can be calculated any further panning operations
			if(!obj.mapcenter) obj.mapcenter = obj.projection.fromLatLngToDivPixel(new google.maps.LatLng(obj.map.getBounds().getCenter().lat(),obj.map.getBounds().getCenter().lng()));
		
			//finally, we can position the data
			this.movedata();	
	}

	//this function moves the circles without checking their data — should be faster than re-checking everything
	//only works for panning (not zooming)
	this.panData = function() {
		//we get the current map center data, and compare it with the map center data from the last time it updated the projection to calculate the offset 
		offset = projection.fromLatLngToDivPixel(new google.maps.LatLng(map.getBounds().getCenter().lat(),map.getBounds().getCenter().lng()));
		var tx = wx+mapcenter.x-offset.x, ty = wy+mapcenter.y-offset.y;
		d3VizObj.runHook("gmap_pan");
		/*
		d3.selectAll(".data circle")
			.attr("transform", "translate("+(tx)+","+(ty)+")");
		*/
	}

	//this function goes over all the data and checks if it is where it ought to be
	this.moveData = function() {
			d3VizObj.runHook("gmap_move");
			//iterate over all the data, transform the x and y positions of the circle to match the pixel positions of the projection
			/*
			svg.selectAll(".data circle")
				.attr("cx", function(d) { return projection.fromLatLngToDivPixel(new google.maps.LatLng(latLon(d)[0],latLon(d)[1])).x;} ) //x position
				.attr("cy", function(d) { return projection.fromLatLngToDivPixel(new google.maps.LatLng(latLon(d)[0],latLon(d)[1])).y;} ) //y position
			;*/
	}

	obj.wx = 0; obj.wy = 0; //this keeps track of previous transformations

	//if the window gets resized, we need to recalculate the bounds of the overlay object (if it has been created)
	//this has bugs -- it doesn't work if you pan and THEN resize the window 
	window.onresize = function() {
		if(obj.overlay) {
			if(obj.mapcenter&&obj.offset) obj.wx = obj.wx+obj.mapcenter.x-obj.offset.x, obj.wy = obj.wy+obj.mapcenter.y-obj.offset.y;
			google.maps.event.trigger(obj.map, 'resize'); //tell Google Maps it has been resized
			obj.mapcenter = obj.projection.fromLatLngToDivPixel(new google.maps.LatLng(obj.map.getBounds().getCenter().lat(),obj.map.getBounds().getCenter().lng()));
		}
	}
}
d3GMap.prototype = new d3Viz(d3GMap);

//automates making a select element
function make_selector(settings) {
	var dv = document.createElement("div");
	if(settings.div_id) dv.id = settings.div_id;
	if(settings.div_class) dv.className = settings.div_class;
	if(settings.caption) {
		var cap = document.createTextNode(settings.caption);
		dv.appendChild(cap);
	}
	var sel = document.createElement("select");
	if(settings.select_id) sel.id = settings.select_id;
	if(settings.dataindex) sel.dataindex = settings.dataindex;
	if(settings.onchange) {
		sel.onchange = settings.onchange;
	}
	for(var i in settings.selector_options) {
		var opt = document.createElement("option");
		opt.text = settings.selector_options[i][0];
		opt.value = i;
		if(settings.default_option) {
			if(i==default_option) opt.selected = true;
		}
		sel.add(opt);
	}
	dv.appendChild(sel);
	if(settings.post_caption) {
		var cap2 = document.createTextNode(settings.post_caption);
		dv.appendChild(cap2);
	}
	if(settings.attach_to_id) {
		document.getElementById(settings.attach_to_id).appendChild(dv);
	} else if(settings.attach_to_element) {
		document[settings.attach_to_element].appendChild(dv);
	}
}

//allows to move an SVG object around
d3.selection.prototype.moveUp = function() {
  return this.each(function(){
    this.parentNode.appendChild(this);
  });
};

//loads a script on the fly
function loadScript(url, callback) {
    // Adding the script tag to the head as suggested before
    var head = document.getElementsByTagName('head')[0];
    var script = document.createElement('script');
    script.type = 'text/javascript';
    script.src = url;

    // Then bind the event to the callback function.
    // There are several events for cross browser compatibility.
    script.onreadystatechange = callback;
    script.onload = callback;

    // Fire the loading
    head.appendChild(script);
}