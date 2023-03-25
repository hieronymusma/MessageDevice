using LiteDB;
using matrix_web.LiteDb;
using matrix_web.Models;
using Microsoft.AspNetCore.Mvc;

namespace matrix_web.Controllers;

[ApiController]
[Route("api/[controller]")]
public class MessagesController : ControllerBase
{
    private static readonly Random rnd = new Random();

    private readonly ILogger<MessagesController> _logger;
    private readonly ILiteDbContext _dbContext;

    public MessagesController(ILogger<MessagesController> logger, ILiteDbContext dbContext)
    {
        _logger = logger;
        _dbContext = dbContext;
    }

    [HttpGet("{id}/last")]
    public ActionResult<Message> GetLastMessage(string id)
    {
        var collection = GetCollection(id);
        var message = collection.Query().Where(x => x.ack == false).OrderBy(x => x.id).FirstOrDefault();
        
        // If we have only acknowledged messages return the last one
        if (message == null && collection.Count() > 0)
            message = collection.FindOne(Query.All(Query.Descending));

        return message != null ? message : NoContent();
    }

    [HttpGet("{id}/previous/{previousCount}")]
    public ActionResult<Message> GetPreviousMessage(string id, int previousCount) {

        var collection = GetCollection(id);
        var message = collection.Query().Where(x => x.ack == true).OrderByDescending(x => x.id).Skip(previousCount).FirstOrDefault();

        return message != null ? message : NoContent();
    }

    [HttpGet("{id}/random")]
    public ActionResult<Message> GetRandomMessage(string id)
    {
        var collection = GetCollection(id);
        var offset = rnd.Next(0, collection.Count());
        var message = collection.Query().Limit(1).Offset(offset).SingleOrDefault();

        return message != null ? message : NoContent();
    }

    [HttpGet("{id}/{message_id}/ack")]
    public IActionResult AckMessage(string id, long message_id)
    {
        var collection = GetCollection(id);
        var message = collection.FindById(message_id);

        if (message == null)
        {
            return NotFound();
        }

        message.ack = true;

        collection.Update(message);

        return Ok();
    }

    [HttpPost("{id}")]
    public IActionResult NewMessage(string id, Message message)
    {
        var collection = GetCollection(id);

        message.ack = false;
        message.date = DateTime.Now;
        message.id = 0;

        var newId = collection.Insert(message);
        
        return Ok();
    }

    private ILiteCollection<Message> GetCollection(string id)
    {
        return _dbContext.Database.GetCollection<Message>(id);
    }
}
