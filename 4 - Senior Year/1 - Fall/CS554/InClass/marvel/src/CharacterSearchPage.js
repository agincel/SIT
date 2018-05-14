import React, { Component } from 'react';
import './App.css';
import axiosInstance from './utils/axiosinstance';

import CharacterList from "./CharacterList";

class CharacterSearchPage extends Component {
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
      <div className="character-search-page">
        <p className="App-intro">
          To get started, please add a hero name below.
        </p>
        <form onSubmit={(e)=> {
            e.preventDefault();
            this.searchForMatches(this.state.searchQuery);
          }}>
          <input type="text" 
          onChange={(e) => {
            e.preventDefault();
            this.changeSearchQuery(e.target.value);
          }}
          value={this.state.searchQuery} />
          <button type="submit">Search</button>
        </form>
        <hr />
        <CharacterList characters={this.state.characterList} />
      </div>
    );
  }
  changeSearchQuery = (searchQuery) => {
    this.setState({searchQuery});
  }

  async searchForMatches(searchQuery) {
    console.log(searchQuery);
    const url = `characters?nameStartsWith=${searchQuery}`;
    console.log(url);
    const response = await axiosInstance.get(url);
    const resultList = response.data.data.results;
    console.log(resultList);
    this.setState({characterList: resultList});
  }
}

export default CharacterSearchPage;
