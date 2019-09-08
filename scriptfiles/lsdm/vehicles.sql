CREATE TABLE IF NOT EXISTS las_venturas (
    id      INTEGER     PRIMARY KEY ASC AUTOINCREMENT
                        NOT NULL,
    model   INTEGER (5) NOT NULL,
    x       FLOAT       NOT NULL,
    y       FLOAT       NOT NULL,
    z       FLOAT       NOT NULL,
    r       FLOAT       NOT NULL,
    color1  TINYINT (3),
    color2  TINYINT (3),
    enabled BOOLEAN     NOT NULL
                        DEFAULT true
);

CREATE TABLE IF NOT EXISTS los_santos (
    id      INTEGER     PRIMARY KEY ASC AUTOINCREMENT
                        NOT NULL,
    model   INTEGER (5) NOT NULL,
    x       FLOAT       NOT NULL,
    y       FLOAT       NOT NULL,
    z       FLOAT       NOT NULL,
    r       FLOAT       NOT NULL,
    color1  TINYINT (3),
    color2  TINYINT (3),
    enabled BOOLEAN     NOT NULL
                        DEFAULT true
);

CREATE TABLE IF NOT EXISTS san_fierro (
    id      INTEGER     PRIMARY KEY ASC AUTOINCREMENT
                        NOT NULL,
    model   INTEGER (5) NOT NULL,
    x       FLOAT       NOT NULL,
    y       FLOAT       NOT NULL,
    z       FLOAT       NOT NULL,
    r       FLOAT       NOT NULL,
    color1  TINYINT (3),
    color2  TINYINT (3),
    enabled BOOLEAN     NOT NULL
                        DEFAULT true
);
