import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import {MatrixModule} from '../matrix/matrix.module';

@NgModule({
  declarations: [
    AppComponent
  ],
    imports: [
        BrowserModule,
        MatrixModule
    ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
