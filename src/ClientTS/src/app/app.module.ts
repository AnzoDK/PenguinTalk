/**
 * This is the main module of the Angular application.
 * It imports the necessary modules and components, and declares the AppComponent.
 * All Angular applications must have at least one module, and it is typically named AppModule.
 */

import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import * as Constants from './constants/constants';
import { MatButtonModule } from '@angular/material/button';
import { ConnectDialogComponent } from './connect-dialog/connect-dialog.component'

@NgModule({
  declarations: [
    AppComponent,
    ConnectDialogComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    BrowserAnimationsModule,
    Constants.angularMaterialModules
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule {}


