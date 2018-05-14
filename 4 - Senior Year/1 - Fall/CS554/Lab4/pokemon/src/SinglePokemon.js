import React, { Component } from 'react';

const request = require('async-request');


function capitalizeFirstLetter(string) {
  return string.charAt(0).toUpperCase() + string.slice(1);
}


class SinglePokemon extends Component {
    constructor(props) {
      super(props);
  
      this.ID = props.match.params.ID;
      this.state =  {
        pokemon: {}
      }
      this.populatePokemon(this.ID);
    }
  
    async populatePokemon(ID) {
      var poke = await request("https://pokeapi.co/api/v2/pokemon/" + ID);
      var pokespecies = await request("https://pokeapi.co/api/v2/pokemon-species/" + ID);
      var ret = JSON.parse(poke.body);
      ret.species = JSON.parse(pokespecies.body);
      this.setState({
        pokemon: ret
      });
    }
  
    render() {
      if (this.state.pokemon.name) {
        return [
          <div key="div">
            <h1 key="name">{capitalizeFirstLetter(this.state.pokemon.name)}</h1>
            <h2 key="id">Pokedex ID: {this.state.pokemon.id}</h2>
            <h3 key="types">{capitalizeFirstLetter(this.state.pokemon.types[0].type.name)} {this.state.pokemon.types.length > 1 ? capitalizeFirstLetter(this.state.pokemon.types[1].type.name) : ""}</h3>
            <p key="h">Height: {this.state.pokemon.height/10}m</p>
            <p key="w">Weight: {this.state.pokemon.weight/10}kg</p>
            <p key="f">{this.state.pokemon.species.flavor_text_entries[1].flavor_text}</p>
  
          </div>
        ]
      } else if (this.state.pokemon.detail) {
        //this usually means 404
        return <p>ERROR: A Pokemon with that ID could not be found.</p>;
      } 
      else {
        return <p>Loading...</p>
      }
    }
  }

  
export default SinglePokemon;