/* KEYWORD FILTERING - by Alex Wellerstein, v2.0 

Keyword filtering is when you have some kind of verbose (text-based) field that you want to be able to toggle on and
off based on what contents are in the field. For example, if your data was "restaurants" and you wanted to be able to
toggle them by whether they served burgers, sandwiches, or soup. In this dataset, you would have one field (say, "food")
that could contain multiple values demarcated by a separator, e.g. "burgers, soup" or "soup, sandwiches, burgers". In this
example the separator is a comma, but you could also use semicolons, space characters, etc. 

The filtering itself works by assigning classes to the data point. So if the data has the keyword searched for, it will
get the class "data_has_keyword". If it doesn't, it gets "data_lacks_keyword". You can use the stylesheet to toggle
what these classes then do. It is easy to set it up to toggle visible based on a keyword and invisible based on lacking it,
but for some functions you might want to do the reverse (e.g. if you have a list of days a restaurant is closed, you could
have the data_lacks_keyword class be visible and the data_has_keyword be invisible, and this would show you whether the 
restaurant was open on the day in question). 

Keywords are searched for in a case-insensitive manner. 

*/

function filterKeywords(options) {
	var obj = this; 
	obj.loadOptions(options);
	d3VizObj.controls.push(obj); obj.id = d3VizObj.controls.length-1;

	this.keywordFilterBuildSelect = function() {
		if(debug) console.log("Building the keyword filter menu");
		var insert = document.getElementById(obj.keywordFilterAttachId);
		if(!insert) {
			if(debug) console.log("Could not find HTML entity with the id '"+obj.keywordFilterAttachId);
		} else {
			var div = document.createElement("div");
			div.id = "keywordFilter_"+obj.id;
			div.class = "keywordFilter";
			var cap = document.createElement("span");
			var cap_content = document.createTextNode(obj.keywordFilterCaption);
			cap.appendChild(cap_content);
			cap.id = "keywordFilter_"+obj.id+"_label";
			div.appendChild(cap);
			var sel = document.createElement("select");
			sel.onchange = function() { obj.keywordFilter(this.value) };			
			for(i in obj.keyword_filter_options) {
				var opt = document.createElement("option");
				opt.text = obj.keyword_filter_options[i][0];
				opt.value = i;
				if(i==obj.keyword_filter_default) opt.selected = true;
				sel.add(opt);
			}
			div.appendChild(sel);
			insert.appendChild(div);
		}
	}
	this.keywordFilter = function(value) {
		if(debug) console.log("Filtering by keyword '"+value+"'");
		obj.map.stage //with the stage
			.selectAll(obj.keyword_filter_data_class) //select all data 
			.data(obj.data.data) //parse the data again 
			.classed("data_has_keyword", function(d) {
				if(value==0) { //all is checked
					return false; //reset
				} else { //but if something else is selected
					var keywords = d[obj.keyword_filter_field].split(obj.keyword_filter_separator); //make an array of all fields in this data field, based on them being separated by commas
					for(i in keywords) { keywords[i] = keywords[i].trim().toLowerCase(); } //get rid of extra spaces and case sensitivity
					if(keywords.indexOf(obj.keyword_filter_options[value][0].toLowerCase())!==-1) { //if the keyword is found
						return true;
						//return keyword_filter_data_class+" data_has_keyword"; //add the data_hilight class, so we can toggle it if we want to make it more visible
					} else { //if it is not found...
						return false;
					}
				}
			})
			.classed("data_lacks_keyword", function(d) {
				if(value==0) { //all is checked
					return false; //reset
				} else { //but if something else is selected
					var keywords = d[obj.keyword_filter_field].split(obj.keyword_filter_separator); //make an array of all fields in this data field, based on them being separated by commas
					for(i in keywords) { keywords[i] = keywords[i].trim().toLowerCase(); } //get rid of extra spaces and case sensitivity
					if(keywords.indexOf(obj.keyword_filter_options[value][0].toLowerCase())!==-1) { //if the keyword is found
						return false;
						//return keyword_filter_data_class+" data_has_keyword"; //add the data_hilight class, so we can toggle it if we want to make it more visible
					} else { //if it is not found...
						return true;
					}
				}
			})
	}
	
	d3VizObj.addHook("run_before_map_loaded",this.keywordFilterBuildSelect);
}
filterKeywords.prototype = new d3Viz(filterKeywords);
if(debug) console.log("Filter by keyword script loaded");