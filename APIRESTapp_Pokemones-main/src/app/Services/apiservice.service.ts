// Importa los módulos necesarios de Angular
import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

// Marca la clase como un servicio inyectable, lo que permite que Angular lo inyecte automáticamente donde sea necesario.
@Injectable({
  providedIn: 'root'
})
export class PokeapiService {
  // Define la URL base de la PokeAPI
  private apiUrl = 'https://pokeapi.co/api/v2/';

  // El constructor recibe una instancia de HttpClient, que será utilizada para realizar solicitudes HTTP.
  constructor(private http: HttpClient) { }

  // Método para obtener información de un Pokémon por su ID.
  // Retorna un Observable, ya que las solicitudes HTTP en Angular son asíncronas.

  getPokemonName(name: string): Observable<any> {
    return this.http.get(this.apiUrl + "pokemon/" + name);
  }

  getPokemonType(types: string): Observable<any> {
    return this.http.get(this.apiUrl + "pokemon/" + types);
  }

}