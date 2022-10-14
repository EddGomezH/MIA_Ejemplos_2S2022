import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class EjemploService {

  constructor(
    private httpClient: HttpClient
  ) { }

  getNombreRandom(){
    return this.httpClient.get("https://randomuser.me/api/");
  }
}
