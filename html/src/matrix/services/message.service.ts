import { Injectable } from '@angular/core';
import {Message} from '../models/message';
import {Observable, of} from 'rxjs';
import {HttpClient, HttpParams} from '@angular/common/http';
import { environment } from '../../environments/environment';
import {catchError} from 'rxjs/operators';

@Injectable({
  providedIn: 'root'
})
export class MessageService {

  constructor(private http: HttpClient) { }

  public save(message: Message): Observable<any>{
    return this.http.post(environment.baseUrl + 'led/messages/save', message).pipe(
      catchError((): Observable<any> => of([])),
    );
  }
}
