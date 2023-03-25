export interface Message {
    id: number,
    date: Date,
    content: string,
    leds: boolean[],
    ack: boolean,
}