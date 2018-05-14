import React, { Component } from 'react';

import {
    Link
  } from 'react-router-dom'

const request = require('async-request');


function capitalizeFirstLetter(string) {
  return string.charAt(0).toUpperCase() + string.slice(1);
}

class BerryList extends Component {
    constructor(props) {
      super(props);
      //console.log(props);
      this.pageNum = props.match.params.pageNum;
      this.state = {
        berryList: []
      };
      this.populateBerryList(this.pageNum);
    }
  
    componentWillReceiveProps(props) {
      //console.log(props);
      this.pageNum = props.match.params.pageNum;
      this.populateBerryList(this.pageNum);
    }
  
    render() {
      var ret =  [
        <h1 key="header">Berrydex Page {this.pageNum}</h1>
      ]
  
      if (this.pageNum > 0) {
        ret.push(<Link key="prev" to={`/berries/page/${parseInt(this.pageNum, 10) - 1}`}>Previous Page</Link>)
      }
      ret.push(<br key="br1" />);
      if (this.pageNum < 2) {
        ret.push(<Link key="next" to={`/berries/page/${parseInt(this.pageNum, 10) + 1}`}>Next Page</Link>)
      }
  
      ret.push(<br key="br2" />);
      ret.push(<br key="br3" />);
  
      for (var i = 0; i < this.state.berryList.length; i++) {
        ret.push(<Link key={"berry" + i} to={"/berries/" + this.state.berryList[i].url.split("/")[6]}>#{this.state.berryList[i].url.split("/")[6]}: {capitalizeFirstLetter(this.state.berryList[i].name)} Berry</Link>);
        ret.push(<br key={"innerBr" + i} />);
      }
  
  
  
      return ret;
    }
  
    async populateBerryList(p) {
      var perPage = 25;
      var poke = await request("https://pokeapi.co/api/v2/berry/?limit=" + perPage + "&offset=" + (p * perPage));
      console.log(JSON.parse(poke.body).results);
      this.setState({
        berryList: JSON.parse(poke.body).results
      });
    }
  }

export default BerryList;