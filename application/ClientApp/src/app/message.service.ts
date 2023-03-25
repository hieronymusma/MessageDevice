import { HttpClient } from '@angular/common/http';
import { Inject, Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Message } from './message';

@Injectable({
  providedIn: 'root'
})
export class MessageService {

  readonly messageBase = "api/messages/";

  constructor(private http: HttpClient, @Inject('BASE_URL') private baseUrl: string) { }

  new(message: Message, id: string): Observable<void> {
    return this.http.post<void>(this.baseUrl + this.messageBase + `${id}/`, message);
  }
}
