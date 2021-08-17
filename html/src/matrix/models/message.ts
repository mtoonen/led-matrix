export enum MessageType {
  TEXT= 'text',
  TEXT_SCROLLING = 'text_scrolling',
  SHAPE = 'shape'
}

export class Message{

  constructor(
    public payload: string,
    public type: MessageType = MessageType.TEXT,
    public r: number = 255,
    public g: number = 0,
    public b: number = 0) {
  }
}
