import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { CreatorComponent } from './creator/creator.component';



@NgModule({
    declarations: [
        CreatorComponent
    ],
    exports: [
        CreatorComponent
    ],
    imports: [
        CommonModule
    ]
})
export class MatrixModule { }
