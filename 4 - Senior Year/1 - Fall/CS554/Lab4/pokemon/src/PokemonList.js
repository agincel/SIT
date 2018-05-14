import React, { Component } from 'react';

import {
    Link
  } from 'react-router-dom'

const request = require('async-request');


function capitalizeFirstLetter(string) {
  return string.charAt(0).toUpperCase() + string.slice(1);
}

class PokemonList extends Component {
    constructor(props) {
      super(props);
      //console.log(props);
      this.pageNum = props.match.params.pageNum;
      this.state = {
        pokemonList: []
      };
      this.populatePokemonList(this.pageNum);
    }
  
    componentWillReceiveProps(props) {
      //console.log(props);
      this.pageNum = props.match.params.pageNum;
      this.populatePokemonList(this.pageNum);
    }
  
    render() {
      var ret =  [
        <h1 key="header">Pokedex Page {this.pageNum}</h1>
      ]
  
      if (this.pageNum > 0) {
        ret.push(<Link key="prev" to={`/pokemon/page/${parseInt(this.pageNum, 10) - 1}`}>Previous Page</Link>)
      }
      ret.push(<br key="br1" />);
      if (this.pageNum < 40) {
        ret.push(<Link key="next" to={`/pokemon/page/${parseInt(this.pageNum, 10) + 1}`}>Next Page</Link>)
      }
  
      ret.push(<br key="br2" />);
      ret.push(<br key="br3" />);
  
      for (var i = 0; i < this.state.pokemonList.length; i++) {
        ret.push(<Link key={"pokemon" + i} to={"/pokemon/" + this.state.pokemonList[i].url.split("/")[6]}>#{this.state.pokemonList[i].url.split("/")[6]}: {capitalizeFirstLetter(this.state.pokemonList[i].name)}</Link>);
        ret.push(<br key={"innerBr" + i} />);
      }
  
  
  
      return ret;
    }
  
    async populatePokemonList(p) {
      var perPage = 25;
      var poke = await request("https://pokeapi.co/api/v2/pokemon/?limit=" + perPage + "&offset=" + (p * perPage));
      console.log(JSON.parse(poke.body).results);
      this.setState({
        pokemonList: JSON.parse(poke.body).results
      });
    }
  
  
  
  }

export default PokemonList;