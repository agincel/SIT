import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';

class App extends Component {
  render() {
    /*return (
      <div className="App">
        <header className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <h1 className="App-title">Welcome to React</h1>
        </header>
        <p className="App-intro">
          To get started, edit <code>src/App.js</code> and save to reload.
        </p>
      </div>
    );*/

    return (
      <div className="row app">
        <div className="col-2 files pane">Left</div>
        <div className="col-6 content pane">Middle</div>
        <div className="col-4 preview pane">Right</div>
      </div>
    )
  }
}

export default App;
