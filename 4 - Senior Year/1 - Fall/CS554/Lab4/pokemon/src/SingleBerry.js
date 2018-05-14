import React, { Component } from 'react';

const request = require('async-request');


function capitalizeFirstLetter(string) {
  return string.charAt(0).toUpperCase() + string.slice(1);
}

class SingleBerry extends Component {
    constructor(props) {
      super(props);
  
      this.ID = props.match.params.ID;
      this.state =  {
        berry: {}
      }
      this.populateBerry(this.ID);
    }
  
    async populateBerry(ID) {
      var poke = await request("https://pokeapi.co/api/v2/berry/" + ID);
      var ret = JSON.parse(poke.body);
      var flavors = ""; 
      for (var i = 0; i < ret.flavors.length; i++) {
        flavors += capitalizeFirstLetter(ret.flavors[i].flavor.name);
        if (i !== ret.flavors.length - 1)
          flavors += ", ";
      }
      this.setState({
        berry: ret,
        flavors: flavors
      });
    }
  
    render() {
      if (this.state.berry.name) {
        return [
          <div key="div">
            <h1 key="name">{capitalizeFirstLetter(this.state.berry.name)} Berry</h1>
            <h2 key="flavors">Flavors: {this.state.flavors}</h2>
            <p key="size">Size: {this.state.berry.size / 10}cm</p>
            <p key="type">Natural Gift Type: {capitalizeFirstLetter(this.state.berry.natural_gift_type.name)}</p>
            <p key="power">Natural Gift Power: {this.state.berry.natural_gift_power}</p>
          </div>
        ]
      } else if (this.state.berry.detail) {
        //this usually means 404
        return <p>ERROR: A Berry with that ID could not be found.</p>;
      } 
      else {
        return <p>Loading...</p>
      }
    }
  }

export default SingleBerry;