import React, { Component } from 'react';

import {
    Link
  } from 'react-router-dom'

const request = require('async-request');


function capitalizeFirstLetter(string) {
  return string.charAt(0).toUpperCase() + string.slice(1);
}

class MachineList extends Component {
    constructor(props) {
      super(props);
      //console.log(props);
      this.pageNum = props.match.params.pageNum;
      this.state = {
        machineList: [],
        loading: true
      };
      this.populateMachineList(this.pageNum);
    }
  
    componentWillReceiveProps(props) {
      //console.log(props);
      this.pageNum = props.match.params.pageNum;
      this.setState({
        machineList: [],
        loading: true
      })
      this.populateMachineList(this.pageNum);
    }
  
    render() {
      var ret =  [
        <h1 key="header">Machinedex Page {this.pageNum}</h1>
      ]
  
      if (this.pageNum > 0) {
        ret.push(<Link key="prev" to={`/machines/page/${parseInt(this.pageNum, 10) - 1}`}>Previous Page</Link>)
      }
      ret.push(<br key="br1" />);
      if (this.pageNum < 122) {
        ret.push(<Link key="next" to={`/machines/page/${parseInt(this.pageNum, 10) + 1}`}>Next Page</Link>)
      }
  
      ret.push(<br key="br2" />);
      ret.push(<br key="br3" />);
  
      for (var i = 0; i < this.state.machineList.length && !this.state.machineList[i].detail; i++) {
        ret.push(<Link key={"pokemon" + i} to={"/machines/" + this.state.machineList[i].id}>{this.state.machineList[i].item.name.toUpperCase()}: {capitalizeFirstLetter(this.state.machineList[i].move.name)} -- {capitalizeFirstLetter(this.state.machineList[i].version_group.name)}</Link>);
        ret.push(<br key={"innerBr" + i} />);
      }

      if (this.state.loading) {
          ret.push(<p>Loading...</p>);
      }
  
  
  
      return ret;
    }
  
    async populateMachineList(p) {
      var perPage = 10;
      var ret = [];
      for (var i = (p * perPage) + 1; i < (p * perPage) + perPage + 1; i++) {
        try {
          var m = await request("https://pokeapi.co/api/v2/machine/" + i);
          ret.push(JSON.parse(m.body));
          //this.setState({
           // machineList: ret
          //})
        } catch (e) {
          console.log(e);
        }
      }
      console.log(ret);
      this.setState({
        machineList: ret,
        loading: false
      });
    }
  }

export default MachineList;