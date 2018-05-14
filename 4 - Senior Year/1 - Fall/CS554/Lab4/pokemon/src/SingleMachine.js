import React, { Component } from 'react';

const request = require('async-request');


function capitalizeFirstLetter(string) {
  return string.charAt(0).toUpperCase() + string.slice(1);
}

class SingleMachine extends Component {
    constructor(props) {
      super(props);
  
      this.ID = props.match.params.ID;
      this.state =  {
        pokemon: {}
      }
      this.populateMachine(this.ID);
    }
  
    async populateMachine(ID) {
      var poke = await request("https://pokeapi.co/api/v2/machine/" + ID);
      var ret = JSON.parse(poke.body);
      console.log(ret);
      this.setState({
        pokemon: ret,
      });
    }
  
    render() {
      if (this.state.pokemon.item) {
        return [
          <div key="div">
            <h1 key="name">{this.state.pokemon.item.name.toUpperCase()} - {capitalizeFirstLetter(this.state.pokemon.move.name)}</h1>
            <p key="size">Version: {this.state.pokemon.version_group.name.toUpperCase()}</p>
          </div>
        ]
      } else if (this.state.pokemon.detail) {
        //this usually means 404
        return <p>ERROR: A Berry with that ID could not be found.</p>;
      } 
      else {
        return <p>Loading...</p>
      }
    }
  }

export default SingleMachine;
