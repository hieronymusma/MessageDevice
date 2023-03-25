import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class AllowedCharactersService {

  constructor() { }

  replace(originalText: string) : string {
    let replacedText = originalText;
    replacedText = replacedText.replace("`", "'");
    replacedText = replacedText.replace("´", "'");
    replacedText = replacedText.replace("‘", "'");
    replacedText = replacedText.normalize("NFD").replace(/\p{Diacritic}/gu, "");
    return replacedText;
  }
}
