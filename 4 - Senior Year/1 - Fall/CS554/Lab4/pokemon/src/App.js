/*
    Adam Gincel
    Pokedex SPA

    I pledge my honor that I have abided by the Stevens Honor System
*/

import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';

import {
  BrowserRouter as Router,
  Route,
  Switch,
  Link
} from 'react-router-dom'

import SingleMachine from "./SingleMachine";
import MachineList from "./MachineList";

import SingleBerry from "./SingleBerry";
import BerryList from "./BerryList";

import SinglePokemon from "./SinglePokemon";
import PokemonList from "./PokemonList";

const Home = () => (
  <div>
    <h2>Home</h2>
    <p className="App-intro">
          Welcome to the single-page Pokedex app. This is a resource for all Pokemon, Berry, and Machine info. 
    </p>

    <p className="App-intro">
      Use the navbar to search for different Pokemon, Berries, Machines, etc.
    </p>
    <ul>
      <li><Link to="/pokemon/page/0">Pokemon List</Link></li>
      <li><Link to="/berries/page/0">Berry List</Link></li>
      <li><Link to="/machines/page/1">Machine List</Link></li>
    </ul>
  </div>
)


class App extends Component {
  render() {
    return (  
      <Router>
        <div className="App">
            <header className="App-header">
              <img src={logo} className="App-logo" alt="logo" />
              <h1 className="App-title">Pokedex!</h1>
            </header>

          <ul>
            <li><Link to="/">Home</Link></li>
            <li><Link to="/pokemon/page/0">Pokemon List</Link></li>
            <li><Link to="/berries/page/0">Berry List</Link></li>
            <li><Link to="/machines/page/1">Machine List</Link></li>
          </ul>
          <p>By Adam Gincel</p>

          <hr/>
          <Switch>
            <Route exact path="/" component={Home}/>
            <Route path="/pokemon/page/:pageNum" component={PokemonList}/>
            <Route path="/pokemon/:ID" component={SinglePokemon}/>
            <Route path="/berries/page/:pageNum" component={BerryList}/>
            <Route path="/berries/:ID" component={SingleBerry}/>
            <Route path="/machines/page/:pageNum" component={MachineList}/>
            <Route path="/machines/:ID" component={SingleMachine}/>
          </Switch>
        </div>
      </Router>
    )
  }

}

export default App;
