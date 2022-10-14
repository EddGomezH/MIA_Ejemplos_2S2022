import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-inicio-app',
  templateUrl: './inicio-app.component.html',
  styleUrls: ['./inicio-app.component.css']
})
export class InicioAppComponent implements OnInit {

  entrada = "";
  salida = "";

  constructor() { }

  ngOnInit(): void {}

  public async onFileSelected(event:any) {
    const file:File = event.target.files[0];
    this.entrada = await file.text();
  }

  ejecutar(){
    this.salida = "--- Resultados ---";
  }
}
