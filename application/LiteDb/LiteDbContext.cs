using LiteDB;

namespace matrix_web.LiteDb;

public class LiteDbContext : ILiteDbContext
{
    static LiteDbContext() {
        BsonMapper.Global.EmptyStringToNull = false;
    }

    public LiteDatabase Database { get; }

    public LiteDbContext(IConfiguration configuration)
    {
        var databasePath = configuration.GetValue<string>("DatabasePath");
        Database = new LiteDatabase(databasePath);
    }
}

