function SVGLines(options) {
	var obj = this;
	obj.loadOptions(options);
	d3VizObj.viz.push(obj); obj.id = d3VizObj.viz.length-1;
	if(typeof obj.svg=="undefined") obj.svg = "stage";
	if(typeof obj.pathgroup=="undefined") obj.pathgroup = "lines";
	if(typeof obj.interpolate =="undefined") obj.interpolate = "linear";
	if(typeof obj.autosort =="undefined") obj.autosort = "true";
	obj.lineData = [];
	obj.lineGroup = [];
	
	
	this.processData = function(r) {
		if(obj.group_by) {
			if(typeof obj.lineGroup[r.d[obj.group_by]] == "undefined") obj.lineGroup[r.d[obj.group_by]] = [];
			obj.lineGroup[r.d[obj.group_by]].push(r.d.i);
		}
		if(obj.map.projection) {
			obj.lineData[r.d.i] = [];
			var latLonArray = obj.LatLons(r.d);
			for(var x in latLonArray) {
				var xy = map.projection([latLonArray[x][1],latLonArray[x][0]]);
				obj.lineData[r.d.i].push({x:xy[0],y:xy[1]});
			}
		}
	}
	this.showData = function() {
		if(debug) console.log("Showing line data");
		
		obj.pathlayer = obj.map.addGroup(obj.pathgroup+"_"+obj.id,map[obj.svg]);
		obj.pathlayer.classed(obj.pathgroup,true);

		obj.linePaths = [];
		obj.line = d3.svg.line()
			.x(function(d) { return d.x})
			.y(function(d) { return d.y})
			.interpolate(obj.interpolate);
			

		for(var x in obj.data.data) {
			var d = obj.data.data[x];
			obj.lineData[x];
			obj.linePaths[d.i] = 
				obj.pathlayer.append("path")
				.datum(d) //bind data to line object?
				.attr("id", "line_"+obj.id+"_"+d.i)
				.attr("i", d.i)
				.attr("class","line_"+obj.id)
				.classed("linegroup_"+obj.id+"_"+(typeof obj.group_by=="undefined"?"":obj.data.data[x][obj.group_by]),typeof obj.group_by=="undefined"?false:true)
				.attr("d", obj.line(obj.lineData[x]))
				.attr("stroke", function() { return obj.pathStrokeColor(obj.data.data[x],x); })
				.attr("stroke-width", function() { return obj.pathStrokeWidth(obj.data.data[x],x); })
				.on("mouseover", function(){ obj.pathMouseover(this.id); ; })  //what to do when the mouse goes over
				.on("mouseout",  function(){ obj.pathMouseout(this.id);  }) //what to do when the mouse is no longer over it		
		}
		if(obj.autosort) obj.sortByStrokeWidth(obj.pathStrokeWidth);
	}
	this.pathStrokeWidth = function(d,i) {
		if(typeof obj.strokeWidth == "undefined") {
			return 1;
		} else if(typeof obj.strokeWidth == "function") {
			return obj.strokeWidth(d,i);
		} else {
			return obj.strokeWidth;
		}
	}
	this.pathStrokeColor = function(d,i) {
		if(typeof obj.strokeColor == "undefined") {
			return "#000";
		} else if(typeof obj.strokeColor == "function") {
			return obj.strokeColor(d,i);
		} else {
			return obj.strokeColor;
		}
	}
	this.pathMouseover = function(path_id) {
		var i = d3.select("#"+path_id).attr("i");
		var d = obj.data.data[i];
		if(typeof obj.mouseover == "function") {
			return obj.mouseover(d,i,obj,path_id);
		} else if(typeof obj.mouseover_caption == "function") {
			obj.map.tooltip.html(obj.mouseover_caption(d,i,obj,path_id));
		} else if(obj.mouseover_caption) {
			obj.map.tooltip.html(obj.mouseover_caption);
		}
	}
	this.pathMouseout = function(path_id) {
		var i = d3.select("#"+path_id).attr("i");
		var d = obj.data.data[i];
		if(typeof obj.mouseout == "function") {
			return obj.mouseout(d,i,obj,path_id);
		}
	}
	this.sortByStrokeWidth = function(strokefunc) {	
		//sorts so that smallest radius always on top
		obj.map.svg.selectAll(".line_"+obj.id) //for each of the paths...
		.sort(function (a,b) { //resort so bigger circles on bottom
			return strokefunc(b) - strokefunc(a);
		});
	}
	d3VizObj.addHook("run_on_each_data_row",this.processData);
	d3VizObj.addHook("run_after_data_and_map_loaded",this.showData);
}
SVGLines.prototype = new d3Viz(SVGLines);

if(debug) console.log("SVGCircles script loaded");