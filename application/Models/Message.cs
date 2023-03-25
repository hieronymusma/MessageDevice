namespace matrix_web.Models;

public class Message {
    [LiteDB.BsonId]
    public long id { get; set; }

    public DateTime date { get; set; }

    public String content { get; set; }

    public bool[] leds { get; set; }

    public bool ack { get; set; }

    public Message(long id, DateTime date, String content, bool[] leds, bool ack) {
        this.id = id;
        this.date = date;
        this.content = content;
        this.leds = leds;
        this.ack = ack;
    }

    public Message() {
        date = DateTime.Now;
        content = "";
        leds = new bool[0];
     }
}