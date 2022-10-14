import { Component, NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { InicioAppComponent } from './componentes/inicio-app/inicio-app.component';
import { LoginComponent } from './componentes/login/login.component';

const routes: Routes = [
  { path: 'inicio', component: InicioAppComponent},
  { path: 'login', component: LoginComponent},
  { path: '**', redirectTo: 'inicio' }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
