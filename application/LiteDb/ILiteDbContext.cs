using LiteDB;

namespace matrix_web.LiteDb;

public interface ILiteDbContext
{
    LiteDatabase Database { get; }
}