import React, { Component } from 'react';

class CharacterList extends Component {
  render() {
    //alert("hello");
    const {characters} = this.props;
    if (this.props.characters.length === 0) {
        return <small>No Characters</small>;
    }

    const characterDisplays = characters.map((character) => {
        const desc = character.description ? (
            <p>{character.description}</p>
        ) : null;

        

        return (
        <div key={character.id}>
            <h1>{character.name}</h1>
            {desc}
        </div>);

    })
    return <section><h2>Characters</h2>
        {characterDisplays}
    </section>;
  }
}

export default CharacterList;
