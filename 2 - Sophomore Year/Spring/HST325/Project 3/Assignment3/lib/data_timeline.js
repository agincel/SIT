/* Timeline support — allows you to have an animated timeline of events, coded by date or time v.2.0

*/


function Timeline(options) {
	var obj = this;
	obj.loadOptions(options);
	d3VizObj.controls.push(obj); obj.id = d3VizObj.controls.length-1;

	this.currentDate = this.stopDate;
	this.lastDate = [];
	this.index = [];


	if(typeof this.default_speed == "undefined") {
		this.timer_tick = 300; //default timer tick (300 ms)
	} else {
		this.timer_tick = this.default_speed;
	}
	this.data_id_prefix = "d_"+obj.id+"_"; //this is how it finds ids — shouldn't need to be changed if you use this template


	this.timer_paused = false;
	this.timer_playing = false;
	this.timer = false;
	
	//create the datetime objects
	this.dateObj = new DateTimeArray();
	this.dateObjStopCompare = DateArrayToNumber(this.stopDate);

	this.addSlider = function() {
		obj.slider_index = [];
		var dob = new DateTimeArray();
		dob.setDateTime(obj.startDate);
		while(DateArrayToNumber(dob.getDateTime())<=DateArrayToNumber(obj.stopDate)) {
			obj.slider_index.push(DateArrayToNumber(dob.getDateTime()));
			dob.addDateTime(obj.dateTick);
		}
		var d = document.createElement("input");
		d.type = "range";
		d.min = 0;
		d.max = obj.slider_index.length-1;
		d.step = 1;
		d.value = obj.slider_index.length-1;
		d.id = "timeline_"+obj.id+"_slider";
		d.className = "timeline_slider";
		d.onchange = obj.timelineSliderChange;			
		document.getElementById(obj.sliderAttachId).appendChild(d); //add it to the document
	}
	if(obj.sliderAttachId) d3VizObj.addHook("run_before_map_loaded",this.addSlider);
	
	//this function creates an array, this.index, that contains all of the data ids coded to their location in the timeline
	//the precision of the index is inferred from the dateInfo option
	this.makeIndex = function () {
		//get the precision of the date change
		for(x = obj.dateTick.length-1; x>=0; x--)  {
			if(obj.dateTick[x]!=0) {
				obj.date_precision = x;
			}
		}

		if(typeof obj.dateInfo=="undefined") {
			obj.index = []; //no index -- only used if this is not how data is being parsed
		} else {
			//set up a function to iterate over the date, grab its information
			d3VizObj.addHook("run_on_each_data_row",
				function(r) {
					r.d.timerDate = obj.dateInfo(r.d);
					var tindex = "";
					for(var x=0;x<=obj.date_precision;x++) {
						tindex+=r.d.timerDate[x];
						if(x<obj.date_precision) tindex+="-";
					}
					if(typeof obj.index[tindex] == "undefined") {
						obj.index[tindex] = [];
					}
					obj.index[tindex].push(r.d.i);
				}
			);
		}	
	}
	this.makeIndex();

	this.addPlaybackInterface = function() {
		var anim = document.getElementById(obj.animatorAttachId);
		//this is crap -- will improve later
		var d = document.createElement("div");
		d.id = "timeline_anim_"+obj.id;
		d.className = "timeline_anim";
		var da = document.createElement("a");
		da.href = "#";
		da.title = "Start animation";
		da.onclick = function() { obj.startTimer();};
		var aT = document.createTextNode("\u25B6");
		da.appendChild(aT);
		d.appendChild(da);
		var aT = document.createTextNode(" "); d.appendChild(aT);
		var da = document.createElement("a");
		da.href = "#";
		da.title = "Pause animation";
		da.onclick = function() { obj.pauseTimer();};
		var aT = document.createTextNode("\u275A\u275A");
		da.appendChild(aT);
		d.appendChild(da);
		var aT = document.createTextNode(" "); d.appendChild(aT);

		if(typeof obj.speeds == "undefined") {
			var speeds = [1,100,200,300,500,1000];
		} else {
			var speeds = obj.speeds;
		}
		if(speeds.length>1) {
			var da = document.createElement("select");
			da.onchange = function() { obj.timeSpeedChange(this.value); };
			da.title = "Animation speed (ms)";
			for(s in speeds) {
				var dao = document.createElement("option");
				dao.text = speeds[s];
				dao.value = speeds[s];
				if(speeds[s]==obj.timer_tick) dao.selected = true;
				da.appendChild(dao);
			}
			d.appendChild(da);
			var aT = document.createTextNode(" "); d.appendChild(aT);
		}
		if(typeof obj.reset =="undefined") {
			var da = document.createElement("a");
			da.href = "#";
			da.title = "Reset all data";
			da.onclick = function() { obj.timeShowAll();};
			var aT = document.createTextNode("Reset");
			da.appendChild(aT);
		} else {
			if(obj.reset==true) {
				var da = document.createElement("a");
				da.href = "#";
				da.title = "Reset all data";
				da.onclick = function() { obj.timeShowAll();};
				var aT = document.createTextNode("Reset");
				da.appendChild(aT);				
			}
		}
		d.appendChild(da);
		var da = document.createElement("br");
		d.appendChild(da);
		var da = document.createElement("span");
		da.id="date_status";
		d.appendChild(da);
		anim.appendChild(d);
	};
	if(obj.animatorAttachId) d3VizObj.addHook("run_before_map_loaded",this.addPlaybackInterface);

	//shows the data for a given year
	this.dataDateTick = function() {
		var curDate = obj.dateObj.getDateTime();

		if(debug&&debug_verbose) console.log("Timeline showing date for "+obj.dateObj.formatDate());

		var tindex = "";
		tindex+=curDate[0];
		if(obj.date_precision>0) tindex+="-"+curDate[1];
		if(obj.date_precision>1) tindex+="-"+curDate[2];
		if(obj.date_precision>2) tindex+="-"+curDate[3];
		if(obj.date_precision>3) tindex+="-"+curDate[4];
		if(obj.date_precision>4) tindex+="-"+curDate[5];

		//tag dates that are in the past
		if(obj.lastDate.length) {
			for(var i in obj.lastDate) {
				 obj.map.svg.selectAll("#"+obj.data_id_prefix+obj.lastDate[i])
					.classed("data_date_past",true)
					.classed("data_date_now",false)
			}	
		}
	
		if(typeof obj.index[tindex]!=="undefined") {
			if(obj.index[tindex].length) {
				for(var i in obj.index[tindex]) {
					//change to now
					 obj.map.svg.selectAll("#"+obj.data_id_prefix+obj.index[tindex][i])
						.classed("data_date_now",true)
						.classed("data_date_future",false);
				}
				obj.lastDate = obj.index[tindex]; 
			}
		}
		//move the slider, if it exists
		if(obj.sliderAttachId) {
			document.getElementById("timeline_"+obj.id+"_slider").value = obj.slider_index.indexOf(obj.dateObj.compareDate());
		}
		//run onDateTick function on data if desired
		if(typeof obj.onDateTick =="function") {
			obj.onDateTick(obj.currentDate);
		}
	}

	this.startTimer = function() {
		if(!obj.timer_playing) {
			if(debug) console.log("Timeline timer started ("+obj.timer_tick+")");
			obj.timer_playing = true;
			obj.currentDate = obj.startDate; //reset the timer
			obj.dateObj.setDateTime(obj.currentDate);
			if(typeof obj.svgElement !=="undefined") {
				obj.map.svg.selectAll(obj.svgElement) //reset all date classes
					.classed("data_date_future",true)
					.classed("data_date_past",false)
					.classed("data_date_now",false)
			}
			obj.dataDateTick(); //display the data for the current time
			obj.timer = setInterval(obj.nextTime,obj.timer_tick); //start timer
			obj.timer_paused = false;
			//move the slider, if it exists
			if(obj.sliderAttachId) document.getElementById("timeline_"+obj.id+"_slider").value = obj.slider_index.indexOf(obj.dateObj.compareDate());
		} else {
			if(obj.timer_paused) { //if it's paused
				if(obj.sliderAttachId) {
					obj.dateObj.currentDate = NumberToDateArray(obj.slider_index[document.getElementById("timeline_"+obj.id+"_slider").value]);
					obj.dataDateTick(); //display the data for the current time
				}
				obj.timer_paused = false; //unpause
				obj.timer = setInterval(obj.nextTime,obj.timer_tick); //start timer
			}
		}	
	}

	this.pauseTimer = function() {
		if(obj.timer_playing) {
			if(obj.timer_paused) { //if it's already paused
				if(debug) console.log("Timeline unpaused");
				obj.timer_paused = false; //unpause
				obj.timer = setInterval(obj.nextTime,obj.timer_tick);
			} else {
				if(debug) console.log("Timeline paused");
				if(obj.timer) { //if a timer exists
					clearInterval(obj.timer); //stop the timer ticking
					obj.timer_paused = true; //indicate it is paused
				}
			}
		}
	}

	//function that is called every time tick interval
	this.nextTime = function() {
		if(debug_verbose&&debug) console.log("Timeline tick for dataset "+obj.id+" ("+obj.datObj.formatDate()+")");

		//we can use the Date/Time object to generate very large numbers that will allow comparisons between dates
		var compareNow  = obj.dateObj.compareDate();
		var compareStop = obj.dateObjStopCompare;

		if(compareNow >= compareStop) { //is now equal or greater to the end? 
			if(debug_verbose&&debug) console.log("Timeline has finished"); 
			clearInterval(obj.timer); //if the current time is greater or equal to the stop time, we stop ticking
			obj.timer_playing = false;
			if(obj.loop) obj.startTimer(); //loop?
		} else { //otherwise, advance the date one tick
			obj.dateObj.addDateTime(obj.dateTick);
			obj.currentDate = obj.dateObj.getDateTime();		
			obj.dataDateTick(); //register the new tick
		}
	}

	//updates the timer speed, pauses and unpauses
	this.timeSpeedChange = function(newTime) {
		if(debug) console.log("Timeline speed changed to "+newTime);
		obj.timer_tick = newTime; //set the new time
		obj.pauseTimer(); //pause it once
		obj.pauseTimer(); //then unpause it
	}


	//resets the timer situation, showing all the data
	this.timeShowAll = function() {
		if(debug) console.log("Timeline showing all data");
		obj.timer_playing=false;
		if(obj.timer) clearInterval(obj.timer);
		obj.timer_paused = false;
		obj.dateObj.setDateTime(obj.stopDate);
		if(typeof obj.svgElement !=="undefined") {
			obj.map.svg.selectAll(obj.svgElement) //clear all classes
				.classed("data_date_future",false)
				.classed("data_date_now",false)
				.classed("data_date_past",false)
			;
		}
		//move the slider, if it exists
		if(obj.sliderAttachId) document.getElementById("timeline_"+obj.id+"_slider").value = obj.slider_index.indexOf(obj.dateObj.compareDate());
	}

	//updates based on the slider changing
	this.timelineSliderChange = function() {
		if(obj.timer_playing) {
			if(!obj.timer_paused) {
				obj.pauseTimer();
			}
		}
	
		obj.timer_playing = true;
		obj.timer_paused = true;

		var val = obj.slider_index[document.getElementById("timeline_"+obj.id+"_slider").value];
	
		if(debug) console.log("Setting view to match "+val+"...");
			obj.currentDate = NumberToDateArray(val);
			obj.dateObj.setDateTime(obj.currentDate);
			if(typeof obj.svgElement !=="undefined") {
				obj.map.svg.selectAll(obj.svgElement) //reset all date classes
					.classed("data_date_future",true)
					.classed("data_date_past",false)
					.classed("data_date_now",false);
			}
			obj.dataDateTick()

			//this is kind of lame but I don't know a better way — looks at all entries in the
			//timelineindex, sees how they compare to the current setting. In theory you could
			//optimize this, if Javascripts indexing order was reliable, but it is not.
			var current = obj.dateObj.compareDate();
			for(var x in obj.index) {
				var indexdate = (DateArrayToNumber(x.split("-")));
				if(indexdate<current) {
					for(var i in obj.index[x]) {
						 obj.map.svg.selectAll("#"+obj.data_id_prefix+obj.index[x][i])
							.classed("data_date_past",true)
							.classed("data_date_future",false)
					}
				} else if(indexdate==current) {
					for(var i in obj.index[x]) {
						obj.map.svg.selectAll("#"+obj.data_id_prefix+obj.index[x][i])
							.classed("data_date_now",true)
							.classed("data_date_future",false)
					}
				}
			}
		if(debug) console.log("View is set");
	}
	if(debug) console.log("Timeline initialized");
}
Timeline.prototype = new d3Viz(Timeline);


//version of the compareDate function below that can be run on arbitrary, unvalidated arrays
function DateArrayToNumber(arr) {
	var cd = "";
	cd+= arr[0]?String("0000"+arr[0]).slice(-4):"0000";
	cd+= arr[1]?String("00"+arr[1]).slice(-2):"00";
	cd+= arr[2]?String("00"+arr[2]).slice(-2):"00";
	cd+= arr[3]?String("00"+arr[3]).slice(-2):"00";
	cd+= arr[4]?String("00"+arr[4]).slice(-2):"00";
	cd+= arr[5]?String("00"+arr[5]).slice(-2):"00";
	return +cd;
}

//opposite of the function above — takes one of those long numbers and turns it into a date
function NumberToDateArray(num) {
	var c = [];
	num = String("00000000000000"+num).slice(-14);
	c.push(+num.slice(0,4));//year
	c.push(+num.slice(4,6));//month
	c.push(+num.slice(6,8));//day
	c.push(+num.slice(8,10));//hour
	c.push(+num.slice(10,12));//min
	c.push(+num.slice(12,14));//sec
	return c;
}

//An array-based date/time object. Ignores time zones and daylight savings. Useful only in very specific contexts,
//like this template, where the time zone aspects of the Javascript Date() object become too much of a pain in the neck.
//This stores dates and times as an array of increasing specificity, i.e. [year,month,day,hour,minute,second]
//Note: it uses 24 hour format (so 00 to 23), and months are by their common numbering (1 = January). 
//By Alex Wellerstein.

function DateTimeArray() {
	var dateTime = [1,2,3];
	this.setDateTime = function(init) {
		dateTime = [];
		if(!init.length) return false;
		dateTime[0] = init[0]; //year
		dateTime[1] = (init.length>1)?init[1]:1; //month
		dateTime[2] = (init.length>2)?init[2]:1; //day
		dateTime[3] = (init.length>3)?init[3]:0; //hour
		dateTime[4] = (init.length>4)?init[4]:0; //minute
		dateTime[5] = (init.length>5)?init[5]:0; //second
		validate();
	}
	
	//adds an array date to the current date. so if the array date added is [0,0,1] it would add one day.
	//if it was [1,0,0] it would add one year. 
	this.addDateTime = function (arr) {
		for(var i = arr.length-1; i>=0; i--) {
			dateTime[i]+=arr[i];
		}
		validate();
	}

	//accessor for the array at its core
	this.getDateTime = function () {
		return dateTime;
	}
	
	//validates a date -- e.g. shifts it around until it is valid
	//currently only counts UP
	function validate() {
		if(typeof dateTime == "undefined") return false;
		if(!dateTime.length) return false;
		//check if too big
		if(dateTime[5]>59) adjustUp(5,59); //second
		if(dateTime[4]>59) adjustUp(4,59); //minute
		if(dateTime[3]>23) adjustUp(3,23); //hour
		if(dateTime[2]>monthMax(dateTime[1],dateTime[0])) adjustUp(2,monthMax(dateTime[1],dateTime[0])-1); //day
		if(dateTime[1]>12) adjustUp(1,11); //month
		//check if too small
		if(dateTime[5]<0) adjustDown(5,0,59); //second
		if(dateTime[4]<0) adjustDown(4,0,59); //minute
		if(dateTime[3]<0) adjustDown(3,0,23); //hour
		if(dateTime[2]<1) adjustDown(2,1,monthMax(dateTime[1]-1,dateTime[0])); //day
		if(dateTime[1]<1) adjustDown(1,1,12); //month
	}
	
	//gets the max days of a month, accounts for leap years
	function monthMax(month,year) {
		while (month<1) month = 12+month;
		switch(month) {
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:
				return 31; break;
			case 4: case 6: case 9: case 11:
				return 30; break;
			case 2: //february, always being a pill
				if(year % 4 !== 0) {
					return 28;
				} else if( year % 100!== 0) {
					return 29;
				} else if( year % 400!== 0) {
					return 28;
				} else {
					return 29;
				}
			break;
		}
	}
	
	//internal adjusters
	function adjustUp(index,max) {
		while(dateTime[index]>max) {
			dateTime[index]-=max+1;
			dateTime[index-1]++;
		}
	}
	function adjustDown(index,min,max) {
		while(dateTime[index]<min) {
			dateTime[index-1]-=1;
			dateTime[index]+=max;
		}
	}
	
	//returns a big number that corresponds with the date info — allows comparisons
	this.compareDate = function() {
		var cd = dateTime[0];
		for(var i = 1; i<dateTime.length;i++) {
			cd+=String("00"+dateTime[i]).slice(-2);
		}
		return +cd;
	}
	
	//outputs an iso8601 formatted date (which can be read by Javascript's Date() object)
	this.formatDate = function() {
		if(typeof dateTime == "undefined") return false;
		if(!dateTime.length) return false;
		var dl = dateTime.length;
		var iso8601 = "";
		iso8601+=dateTime[0]; //year
		if(dl>1) iso8601+="-"+String("00"+Math.max(1,dateTime[1])).slice(-2); //month
		if(dl>2) iso8601+="-"+String("00"+Math.max(1,dateTime[2])).slice(-2); //day
		if(dl>3) iso8601+="T"+String("00"+dateTime[3]).slice(-2); //hour
		if(dl>4) iso8601+=":"+String("00"+dateTime[4]).slice(-2); //min
		return iso8601;
	}
}

/*! rangeslider.js - v1.2.1 | (c) 2015 @andreruffert | MIT license | https://github.com/andreruffert/rangeslider.js */
//!function(a){"use strict";"function"==typeof define&&define.amd?define(["jquery"],a):a("object"==typeof exports?require("jquery"):jQuery)}(function(a){"use strict";function b(){var a=document.createElement("input");return a.setAttribute("type","range"),"text"!==a.type}function c(a,b){var c=Array.prototype.slice.call(arguments,2);return setTimeout(function(){return a.apply(null,c)},b)}function d(a,b){return b=b||100,function(){if(!a.debouncing){var c=Array.prototype.slice.apply(arguments);a.lastReturnVal=a.apply(window,c),a.debouncing=!0}return clearTimeout(a.debounceTimeout),a.debounceTimeout=setTimeout(function(){a.debouncing=!1},b),a.lastReturnVal}}function e(a){return a&&(0===a.offsetWidth||0===a.offsetHeight||a.open===!1)}function f(a){for(var b=[],c=a.parentNode;e(c);)b.push(c),c=c.parentNode;return b}function g(a,b){function c(a){"undefined"!=typeof a.open&&(a.open=a.open?!1:!0)}var d=f(a),e=d.length,g=[],h=a[b];if(e){for(var i=0;e>i;i++)g[i]=d[i].style.cssText,d[i].style.display="block",d[i].style.height="0",d[i].style.overflow="hidden",d[i].style.visibility="hidden",c(d[i]);h=a[b];for(var j=0;e>j;j++)d[j].style.cssText=g[j],c(d[j])}return h}function h(b,e){if(this.$window=a(window),this.$document=a(document),this.$element=a(b),this.options=a.extend({},l,e),this.polyfill=this.options.polyfill,this.onInit=this.options.onInit,this.onSlide=this.options.onSlide,this.onSlideEnd=this.options.onSlideEnd,this.polyfill&&k)return!1;this.identifier="js-"+i+"-"+j++,this.startEvent=this.options.startEvent.join("."+this.identifier+" ")+"."+this.identifier,this.moveEvent=this.options.moveEvent.join("."+this.identifier+" ")+"."+this.identifier,this.endEvent=this.options.endEvent.join("."+this.identifier+" ")+"."+this.identifier,this.toFixed=(this.step+"").replace(".","").length-1,this.$fill=a('<div class="'+this.options.fillClass+'" />'),this.$handle=a('<div class="'+this.options.handleClass+'" />'),this.$range=a('<div class="'+this.options.rangeClass+'" id="'+this.identifier+'" />').insertAfter(this.$element).prepend(this.$fill,this.$handle),this.$element.css({position:"absolute",width:"1px",height:"1px",overflow:"hidden",opacity:"0"}),this.handleDown=a.proxy(this.handleDown,this),this.handleMove=a.proxy(this.handleMove,this),this.handleEnd=a.proxy(this.handleEnd,this),this.init();var f=this;this.$window.on("resize."+this.identifier,d(function(){c(function(){f.update()},300)},20)),this.$document.on(this.startEvent,"#"+this.identifier+":not(."+this.options.disabledClass+")",this.handleDown),this.$element.on("change."+this.identifier,function(a,b){if(!b||b.origin!==f.identifier){var c=a.target.value,d=f.getPositionFromValue(c);f.setPosition(d)}})}var i="rangeslider",j=0,k=b(),l={polyfill:!0,rangeClass:"rangeslider",disabledClass:"rangeslider--disabled",fillClass:"rangeslider__fill",handleClass:"rangeslider__handle",startEvent:["mousedown","touchstart","pointerdown"],moveEvent:["mousemove","touchmove","pointermove"],endEvent:["mouseup","touchend","pointerup"]};h.prototype.init=function(){this.update(!0),this.$element[0].value=this.value,this.onInit&&"function"==typeof this.onInit&&this.onInit()},h.prototype.update=function(a){a=a||!1,a&&(this.min=parseFloat(this.$element[0].getAttribute("min")||0),this.max=parseFloat(this.$element[0].getAttribute("max")||100),this.value=parseFloat(this.$element[0].value||this.min+(this.max-this.min)/2),this.step=parseFloat(this.$element[0].getAttribute("step")||1)),this.handleWidth=g(this.$handle[0],"offsetWidth"),this.rangeWidth=g(this.$range[0],"offsetWidth"),this.maxHandleX=this.rangeWidth-this.handleWidth,this.grabX=this.handleWidth/2,this.position=this.getPositionFromValue(this.value),this.$element[0].disabled?this.$range.addClass(this.options.disabledClass):this.$range.removeClass(this.options.disabledClass),this.setPosition(this.position)},h.prototype.handleDown=function(a){if(a.preventDefault(),this.$document.on(this.moveEvent,this.handleMove),this.$document.on(this.endEvent,this.handleEnd),!((" "+a.target.className+" ").replace(/[\n\t]/g," ").indexOf(this.options.handleClass)>-1)){var b=this.getRelativePosition(a),c=this.$range[0].getBoundingClientRect().left,d=this.getPositionFromNode(this.$handle[0])-c;this.setPosition(b-this.grabX),b>=d&&b<d+this.handleWidth&&(this.grabX=b-d)}},h.prototype.handleMove=function(a){a.preventDefault();var b=this.getRelativePosition(a);this.setPosition(b-this.grabX)},h.prototype.handleEnd=function(a){a.preventDefault(),this.$document.off(this.moveEvent,this.handleMove),this.$document.off(this.endEvent,this.handleEnd),this.$element.trigger("change",{origin:this.identifier}),this.onSlideEnd&&"function"==typeof this.onSlideEnd&&this.onSlideEnd(this.position,this.value)},h.prototype.cap=function(a,b,c){return b>a?b:a>c?c:a},h.prototype.setPosition=function(a){var b,c;b=this.getValueFromPosition(this.cap(a,0,this.maxHandleX)),c=this.getPositionFromValue(b),this.$fill[0].style.width=c+this.grabX+"px",this.$handle[0].style.left=c+"px",this.setValue(b),this.position=c,this.value=b,this.onSlide&&"function"==typeof this.onSlide&&this.onSlide(c,b)},h.prototype.getPositionFromNode=function(a){for(var b=0;null!==a;)b+=a.offsetLeft,a=a.offsetParent;return b},h.prototype.getRelativePosition=function(a){var b=this.$range[0].getBoundingClientRect().left,c=0;return"undefined"!=typeof a.pageX?c=a.pageX:"undefined"!=typeof a.originalEvent.clientX?c=a.originalEvent.clientX:a.originalEvent.touches&&a.originalEvent.touches[0]&&"undefined"!=typeof a.originalEvent.touches[0].clientX?c=a.originalEvent.touches[0].clientX:a.currentPoint&&"undefined"!=typeof a.currentPoint.x&&(c=a.currentPoint.x),c-b},h.prototype.getPositionFromValue=function(a){var b,c;return b=(a-this.min)/(this.max-this.min),c=b*this.maxHandleX},h.prototype.getValueFromPosition=function(a){var b,c;return b=a/(this.maxHandleX||1),c=this.step*Math.round(b*(this.max-this.min)/this.step)+this.min,Number(c.toFixed(this.toFixed))},h.prototype.setValue=function(a){a!==this.value&&this.$element.val(a).trigger("input",{origin:this.identifier})},h.prototype.destroy=function(){this.$document.off("."+this.identifier),this.$window.off("."+this.identifier),this.$element.off("."+this.identifier).removeAttr("style").removeData("plugin_"+i),this.$range&&this.$range.length&&this.$range[0].parentNode.removeChild(this.$range[0])},a.fn[i]=function(b){var c=Array.prototype.slice.call(arguments,1);return this.each(function(){var d=a(this),e=d.data("plugin_"+i);e||d.data("plugin_"+i,e=new h(this,b)),"string"==typeof b&&e[b].apply(e,c)})}});

if(debug) console.log("Timeline script loaded");
