import { Component, OnInit } from '@angular/core';
import { EjemploService } from 'src/app/servicios/ejemplo.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {

  idparticion = "";
  user = "";
  pwd = "";

  constructor(public ejemploService: EjemploService) { }

  ngOnInit(): void {
    this.ejemploService.getNombreRandom().subscribe((res: any) => {
      this.user = JSON.parse(JSON.stringify(res.results[0].name.first));
      this.idparticion = JSON.parse(JSON.stringify(res.results[0].phone));
    });
  }

  ingresar(){
    console.log("ID Particion: ", this.idparticion);
    console.log("User: ", this.user);
    console.log("Password: ", this.pwd);
  }

}
