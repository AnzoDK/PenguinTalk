import { Component } from '@angular/core';
import * as Constants from './constants/constants'
@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = Constants.AppName;
  isLoggedIn: boolean = false;
}
