import { Component, OnInit } from '@angular/core';
import { DomSanitizer } from '@angular/platform-browser';
import { EjemploService } from 'src/app/servicios/ejemplo.service';

@Component({
  selector: 'app-reportes',
  templateUrl: './reportes.component.html',
  styleUrls: ['./reportes.component.css']
})
export class ReportesComponent implements OnInit {

  imagePath: any;

  constructor(private _sanitizer: DomSanitizer, public service: EjemploService) { }

  ngOnInit(): void {
    this.service.getReporte().subscribe((res:any) => {
      let img = JSON.parse(JSON.stringify(res.result))
      this.imagePath = this._sanitizer.bypassSecurityTrustResourceUrl(img);
    });
  }

}
