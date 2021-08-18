import {Component, OnInit} from '@angular/core';
import {Message, MessageType} from '../models/message';
import {AbstractControl, FormControl, Validators} from '@angular/forms';
import {Color} from '@angular-material-components/color-picker';
import {ColorEvent} from 'ngx-color';
import {MessageService} from '../services/message.service';

@Component({
  selector: 'matrix-creator',
  templateUrl: './creator.component.html',
  styleUrls: ['./creator.component.css']
})
export class CreatorComponent implements OnInit {

  public enumKeys = [];
  public selectedmessagetype = MessageType.TEXT;
  public mt = MessageType;
  public color = new Color(255, 143, 0);
  public model = new Message('', MessageType.TEXT_SCROLLING);

  constructor(private message: MessageService) {
    this.enumKeys = Object.keys(this.mt);
  }


  ngOnInit(): void {
  }

  public colorChanged(event: ColorEvent): void {
    this.color = new Color(event.color.rgb.r, event.color.rgb.g, event.color.rgb.b);
    this.model.r = event.color.rgb.r;
    this.model.g = event.color.rgb.g;
    this.model.b = event.color.rgb.b;
  }

  public typeChanged(type: string): void{

    this.model.type = this.mt[type];
  }

  public send(): void {
    this.message.save(this.model).subscribe(v => {
      console.log('saved:', v);
    });
  }

}
