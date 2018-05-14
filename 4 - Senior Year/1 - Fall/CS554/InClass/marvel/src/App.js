import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';
import axiosInstance from './utils/axiosinstance';

import CharacterList from "./CharacterList";
import CharacterSearchPage from "./CharacterSearchPage.js";

import ReactRouter, {
  BrowserRouter as Router,
  Route,
  Link
} from 'react-router-dom';

class App extends Component {
  constructor(props) {
    super(props);

    this.state = {
      searchQuery: "",
      characterList: []
    }
  }


  render() {
    //alert("hello");
    return (
      <div className="App">
        <div className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <h2>{this.props.title}</h2>
          <cite>Brought to you by {this.props.author}</cite>
        </div>
        <CharacterSearchPage />
      </div>
    );
  }
}

export default App;
