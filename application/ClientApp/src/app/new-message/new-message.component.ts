import { Component, OnInit } from '@angular/core';
import { MatCheckboxChange } from '@angular/material/checkbox';
import { MatSnackBar } from '@angular/material/snack-bar';
import { AllowedCharactersService } from '../allowed-characters.service';
import { Message } from '../message';
import { MessageService } from '../message.service';

@Component({
  selector: 'app-new-message',
  templateUrl: './new-message.component.html',
  styleUrls: ['./new-message.component.css']
})
export class NewMessageComponent {
  // We missuse the radio buttons for design reasons
  // "" equals false
  // null equals true
  static readonly emptyLedConfig = [
    ["", "", "", "", "", "", "", ""],
    ["", "", "", "", "", "", "", ""],
    ["", "", "", "", "", "", "", ""],
    ["", "", "", "", "", "", "", ""],
    ["", "", "", "", "", "", "", ""],
    ["", "", "", "", "", "", "", ""],
    ["", "", "", "", "", "", "", ""],
    ["", "", "", "", "", "", "", ""],
  ];

  leds: (string|null)[][] = NewMessageComponent.emptyLedConfig;
  content: string = "";
  receivers: string[] = ["DeviceA", "DeviceB"];
  selectedReceiver: string | null = this.receivers[0];
  sendDisabled: boolean = false;
  
  constructor(private messageService: MessageService, private snackBar: MatSnackBar, private allowedCharacters: AllowedCharactersService) { }

  send() {
    if (this.selectedReceiver == null) throw new Error("Selected receiver must not be null.");
    let message: Message = {
      content: this.content,
      ack: false,
      date: new Date(),
      id: -1,
      leds: this.leds.flat().map((x) => x == "" ? false : true)
    };
    this.sendDisabled = true;
    this.messageService.new(message, this.selectedReceiver).subscribe(() => {
      this.sendDisabled = false;
      this.snackBar.open("Message successful send!", "Close");
      this.clear();
    });
  }

  onInputMessageChange(eventData: string) {
    this.content = this.allowedCharacters.replace(eventData);
  }

  clear() {
    this.content = "";
    this.leds = NewMessageComponent.emptyLedConfig;
  }

  clearDrawing() {
    this.leds = NewMessageComponent.emptyLedConfig;
  }

  checkState(row: number, column: number) {
    let copiedArray = JSON.parse(JSON.stringify(this.leds));
    let oldState = copiedArray[row][column];
    copiedArray[row][column] = oldState == "" ? null : "";
    this.leds = copiedArray;
  }
}
