//a few generic functions that are useful for this kind of map -- should not need to be modified

//resizes the svg to the window whenever the window size changes
function updateWindow(){
	var w = window;
	var window_width = w.innerWidth || e.clientWidth || g.clientWidth;
	var window_height = w.innerHeight|| e.clientHeight|| g.clientHeight;

	svg.attr("height", window_height);
}
window.onresize = updateWindow;

//manually adds a caption point
function add_caption_point(lat,lon,text,angle,xoffset,yoffset,fontsize,circle,radius) {
	if(!projection) return false;
	if(typeof lat=="undefined") return false;
	if(typeof lon=="undefined") return false;
	if(typeof text=="undefined") text = "";
	if(typeof angle=="undefined") angle = -20;
	if(typeof xoffset=="undefined") xoffset = 8;
	if(typeof yoffset=="undefined") yoffset = 5;
	if(typeof fontsize=="undefined") fontsize = "";
	if(typeof circle=="undefined") circle = false;
	if(typeof radius=="undefined") radius = 3;
	
	var gpoint = captions.append("g").attr("class", "gpoint");
	var x = projection([lon,lat])[0];
	var y = projection([lon,lat])[1];
	
	if(circle) {
		gpoint.append("svg:circle")
			.attr("cx", x)
			.attr("cy", y)
			.attr("class","label_point")
			.attr("r", radius+"px")
	}

	//conditional in case a point has no associated text
	if(text.length>0){
		gpoint.append("text")
			.attr("transform", function() { return "translate("+(x+xoffset)+","+(y+yoffset)+")"+ (angle!==false?" rotate("+angle+")":"")})
			.style("font-size", function() { return (fontsize?(fontsize+"px"):""); })
			.attr("class","label")
			.text(text);
	}
}

/* stage zoomer — lets you zoom in/out by clicking on things -- should not need to touch! */

var _path_strokes; //holds the data on the original line widths
var _circle_strokes;  //ditto strokes
var zoom_factor = 1; //keeps track of whether we are zoomed or not, and by how much

//this zooms the mouse in if you click on something
//you shouldn't need to modify anything here...
function zoom_it(d) {
	var x, y;
	var zoom_stage = stage; //set this to whatever big <g> element holds everything that should be zoomed
	//x and y are the pixel positions to center on
	//k is the zoom level
	if(!d&& !centered) {
		x = d3.mouse(this)[0];
		y = d3.mouse(this)[1];
		zoom_factor = 3;
		centered = true;
	} else if(!d && centered) {	//special case for clicking on things without positions
		x = width / 2;
		y = height / 2;
		zoom_factor = 1;
		centered = null;
	} else if(d.positions && centered !==d) { //if you click on something that has a "positions" property, it will center on it — this makes circles clickable
		x = d.positions[0];
		y = d.positions[1];
		zoom_factor = 5;
		centered = d;
	} else if (d && centered !== d) { //if you click on anything else that had position data (like a landform), it will figure out the center of it and them zoom on it
		var centroid = path.centroid(d);
		x = centroid[0];
		y = centroid[1];
		zoom_factor = 3;
		centered = d;
	} else { //if it detects it is already zoomed it, it zooms back out
		x = width / 2;
		y = height / 2;
		zoom_factor = 1;
		centered = null;
	}

	//by default this only attends to paths and circles
	//you could adopt it to also attend to other things with stroke-widths that you wanted to modify on the fly (so they aren't chunky when you zoom in)

	zoom_stage.selectAll("path")
	  .classed("active", centered && function(d) { return d === centered; });

	if(!_path_strokes) {
		_path_strokes = parseFloat(stage.select("path").style("stroke-width"));
	}
	if(!_circle_strokes) {
		_circle_strokes = parseFloat(stage.select("circle").style("stroke-width"));
	}
	zoom_stage.transition()
	  .duration(750)
	  .attr("transform", "translate(" + width / 2 + "," + height / 2 + ")scale(" + zoom_factor + ")translate(" + -x + "," + -y + ")")
	  .selectAll("path")
	  	.style("stroke-width",_path_strokes/zoom_factor)
	;
	d3.selectAll("circle").transition()
	  	.style("stroke-width",_circle_strokes/zoom_factor)
	; 
}


var debug_verbose = false;

function load_map(mapfile) {
	if(mapfile) {
		d3.json(mapfile, function(error, world) {
			if(debug) console.log("Loading mapfile ("+mapfile+")");
			//this "switch" just makes this compatible with the two main types of map files
			switch(world.type) {
				case "FeatureCollection": 
				landforms.append("g")
					.selectAll(".land_boundaries")
					.data(world.features)
					.enter().append("path")
					.attr("class", function(d){ return d.properties.name; })
					.classed("boundaries",true)
					.attr("d", path)
					;
				break;
				case "Topology":
					var lands = landforms.append("g").attr("class","land");
					var boundaries = landforms.append("g").attr("class","boundaries");
					var map_ids = []; //keep track of ids so we can iterate them
					var xx = []; //this is 
					for(x in world.objects) xx.push(x);
					for(y in xx) {
						x = xx[y];
						if(world.objects[x].type=="MultiPolygon") {
   						  if(debug) console.log("Loading map object: "+x);
						  lands.append("path")
							  .datum(topojson.feature(world, world.objects[x]))
							  .classed("map_"+x,true)
							  .classed("map",true)
							  .classed("map_polygon",true)
							  .attr("d", path)
							  ;	
						} else if(world.objects[x].type=="GeometryCollection") {
						  if(debug) console.log("Loading map object: "+x);
						  boundaries.selectAll(".boundaries")
							  .data(topojson.feature(world, world.objects[x]).features)
							  .enter()
							  .append("path")
							  .each(function(d) {
							  	if(typeof d.id!="undefined") { 
									var did = String(d.properties.id).replace(" ","_").replace(",","");
									if(typeof map_ids[did] == "undefined") map_ids[did] = [];
									var m_i = "id_"+did;
									if(map_ids[did].length>0) m_i+="_"+(map_ids[did].length);
									map_ids[did].push(m_i);
									if(debug_verbose&&debug) console.log("Identified map item "+m_i);
									d3.select(this).attr("id",m_i);
							  	}
							  	if(typeof d.properties!="undefined") {
							  		if(typeof d.properties.id !="undefined") {
										var did = String(d.properties.id).replace(" ","_").replace(",","");
										if(typeof map_ids[did] == "undefined") map_ids[did] = [];
										var m_i = "id_"+did;
										if(map_ids[did].length>0) m_i+="_"+(map_ids[did].length);
								  		map_ids[did].push(m_i);
							  			if(debug_verbose&&debug) console.log("Identified map item "+m_i);
										d3.select(this).attr("id",m_i);
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
							  })
							  .classed("map_"+x,true)
							  .classed("map",true)
							  .classed("boundary",true)
							  .attr("d", path)
							  ;	
						} else {
							if(debug) console.log("Unknown map object: "+world.objects[x]);
						}
				}
				 break;
			}
			console.log(map_ids);
			if(debug) console.log("Mapfile loaded");
			//hook
			/*if(run_after_map_loaded.length) {
				for(i in run_after_map_loaded) {
					if(typeof run_after_map_loaded[i] == "function") run_after_map_loaded[i]();
				}
			}
			is_loaded("map");*/
		});
	} else {
		if(debug) console.log("Mapfile explicitly not loaded because no mapfile defined");
		//hook
		/*if(run_after_map_loaded.length) {
			for(i in run_after_map_loaded) {
				if(typeof run_after_map_loaded[i] == "function") run_after_map_loaded[i]();
			}
		}
		is_loaded("map");*/
	}
}

var rad2deg = 180/Math.PI;
var deg2rad = Math.PI/180;

function getbearing(lat1,lon1,lat2,lon2) {
	lat1*=(deg2rad);
	lat2*=(deg2rad);
	lon1*=(deg2rad);
	lon2*=(deg2rad);
	var y = Math.sin(lon2-lon1) * Math.cos(lat2);
	var x = Math.cos(lat1)*Math.sin(lat2) -
			Math.sin(lat1)*Math.cos(lat2)*Math.cos(lon2-lon1);
	var brng = (Math.atan2(y, x) * (rad2deg));
	return brng;
}

//gets the lat/lon destination of a given distance (meters) and a given bearing (degrees) from a given lat/lon point
function get_destination(lat,lon,bearing,dist) {
	var lat1 = lat*(deg2rad);
	var lon1 = lon*(deg2rad);
	var d = dist; 
	var R = 6371000;
	var R = 6378137; //m (equatorial)
	var brng = bearing*deg2rad;
	var lat2 = Math.asin( Math.sin(lat1)*Math.cos(d/R) + 
				  Math.cos(lat1)*Math.sin(d/R)*Math.cos(brng) );
	var lon2 = lon1 + Math.atan2(Math.sin(brng)*Math.sin(d/R)*Math.cos(lat1), 
						 Math.cos(d/R)-Math.sin(lat1)*Math.sin(lat2));
	lat2*=rad2deg;
	lon2*=rad2deg;
	return [lat2,lon2];
}

