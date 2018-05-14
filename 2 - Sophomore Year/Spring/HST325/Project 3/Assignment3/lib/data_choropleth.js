/* SVG CHOROPLETH - by Alex Wellerstein, v2.0 

This allows you to assign colors to map path objects. The TopoJSON map file must have a field in it
that corresponds with a county or country or whatever. So the worldmap-50m.json file has an "id" field
for each country which corresponds to the ISO 3166-1 numerica country code (http://en.wikipedia.org/wiki/ISO_3166-1). 
The us.counties.json file maps US counties and states based on FIPS codes (http://en.wikipedia.org/wiki/FIPS_county_code). Note that the first two numbers of a county FIPS code is its state FIPS code.

The shared.js file has functions for converting country names to ISO codes (and vice versa) and state/counties to FIPS (and vice versa)


*/


function SVGChoropleth(options) {
	var obj = this;
	obj.loadOptions(options);
	d3VizObj.viz.push(obj); obj.id = d3VizObj.viz.length-1;
	if(debug) console.log("Initiating choropleth on dataset "+obj.data.id);
	obj.index = [];

	this.showData = function() {
		for(var d in obj.data.data) { //parse over data	
			if(typeof obj.id_field =="function") {
				var dd = obj.id_field(obj.data.data[d]);
			} else {
				var dd = obj.data.data[d][obj.id_field];
			}
			obj.index[dd] = d;
			obj.map.landforms.selectAll(".map_"+obj.map_data_class+"#id_"+dd) //select each item in the map
				.style("fill",obj.color_scale(obj.color_field(obj.data.data[d]))) //make it the right color
				.on("mouseover", function(d){ obj.choroMouseover(d) })  //what to do when the mouse goes over
				.on("mousemove", function(d){ obj.choroMousemove(d) })  //what to do when the mouse goes over
				.on("mouseout",  function(d){ obj.choroMouseout(d); }) //what to do when the mouse is no longer over it
				.on("click", function(d) { obj.choroMouseclick(d); }); //what to do if clicked
				; 
		}
	}
	this.choroMouseover = function(d) {
		if(typeof obj.mouseover_caption == "function") {
			obj.map.tooltip.html(obj.mouseover_caption(obj.data.data[obj.index[d.id]]));
		} else if(obj.mouseover_caption) {
			obj.map.tooltip.html(obj.mouseover_caption);
		}
		if(typeof obj.mouseover == "function") {
			obj.mouseover(obj.data.data[obj.index[d.id]],d);
		}
	
	}
	this.choroMousemove = function(d) {
		if(typeof obj.mousemove == "function") {
			obj.mousemove(obj.data.data[obj.index[d.id]],d);
		}
	}
	this.choroMouseout = function(d) {
		if(typeof obj.mouseover_caption == "function") {
			obj.map.tooltip.html("");
		}
		if(typeof obj.mouseout == "function") {
			obj.mouseout(d);
		}
	}
	this.choroMouseclick = function(d) {
		if(typeof obj.mouseclick == "function") {
			obj.mouseclick(obj.data.data[obj.index[d.id]],d);
		}	
	}
	d3VizObj.addHook("run_after_data_and_map_loaded",this.showData);
}
SVGChoropleth.prototype = new d3Viz(SVGChoropleth);
if(debug) console.log("SVGChoropleth script loaded");