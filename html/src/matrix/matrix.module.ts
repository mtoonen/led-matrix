import {NgModule} from '@angular/core';
import {CommonModule} from '@angular/common';
import {CreatorComponent} from './creator/creator.component';
import {MatSelectModule} from '@angular/material/select';
import {MatInputModule} from '@angular/material/input';
import {FormsModule} from '@angular/forms';
import {ColorSketchModule} from 'ngx-color/sketch';
import {ColorCircleModule} from 'ngx-color/circle';
import {MatButtonModule} from '@angular/material/button';
import {HttpClientModule} from '@angular/common/http';


@NgModule({
    declarations: [
        CreatorComponent
    ],
    exports: [
        CreatorComponent
    ],
  imports: [
    CommonModule,
    FormsModule,
    MatSelectModule,
    MatButtonModule,
    ColorSketchModule,
    HttpClientModule,
    MatInputModule,
    ColorCircleModule
  ],
})
export class MatrixModule { }
