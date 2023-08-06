import { ChangeDetectorRef, Component, OnInit, Renderer2 } from '@angular/core';
import * as Constants from './constants/constants'
import { MatButton } from '@angular/material/button';
import { mixinColor } from '@angular/material/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit{
  title = Constants.AppName;
  isLoggedIn: boolean = false;
  
  toggle: boolean = true;
  status: string = 'Enable';

  isActive: boolean = true;

  darkMode: boolean = true;

  constructor(private renderer: Renderer2){}

  ApplyTheme(): void
  {
    if (this.darkMode) 
    {
      this.renderer.addClass(document.body, 'dark-mode');
    }
    else
    {
      this.renderer.removeClass(document.body, 'dark-mode');
    }
  }

  ToggleDarkMode(): void
  {
    this.darkMode = !this.darkMode;
    this.ApplyTheme();
  }

  ngOnInit(): void 
  {
    this.ApplyTheme();
  }

  ChangeColor(): void
  {
    this.toggle = !this.toggle;
    this.status = this.toggle ? 'Enable' : 'Disable';
  }

}