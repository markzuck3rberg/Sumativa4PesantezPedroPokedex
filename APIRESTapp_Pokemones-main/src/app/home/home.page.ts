// home.page.ts
import { Component } from '@angular/core';
import { Firestore, doc, setDoc } from '@angular/fire/firestore';
import { PokeapiService } from './../Services/apiservice.service';

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage {
  constructor(private api: PokeapiService, private db: Firestore) {}

  pokemon2: any;
  name2 = '';
  tipoke: any;

  async getPokemonData2(name2: string) {
    try {
      this.tipoke = doc(this.db, 'tipopokemon', 'tipos');
      this.api.getPokemonName(name2).subscribe(async (response) => {
        this.pokemon2 = response;
        const types = this.pokemon2.types;
        await setDoc(this.tipoke, { tipo: types[0].type.name });
      });
    } catch (error) {
      console.log(error);
    }
  }
  
 
  getPokemonTypeClass() {
    if (this.pokemon2 && this.pokemon2.types && this.pokemon2.types[0]) {
      const pokemonType = this.pokemon2.types[0].type.name.toLowerCase();
      return pokemonType;
    } else {
      return 'default-color'; // Clase predeterminada para el color de fondo
    }
  }

  
}

