# Bases

- Core: mor related to the sql language and operations over the db in a pythonic way
- ORM: abstracion of language to manipulate db throung python objects


# Core

- SELECT: r = select(users) <=> select * from users
- FILTER: r = select(users.c.name).where(users.c.name == 'juan')
- JOIN: select(<tables>).join(<table2>, <table1.pk> == <table2.pk>)
- ORDER: select(<table>).order_by(desc(<att>))
- GROUP: select(func.count(<att1>)).group_by(<att2>)

# Schemas

- insert(), update(), delete() used to alterate tables
- with engine.connect() as conn:
    r = conn.execute(stmt) # where stmt can be some statment of above
    conn.commit()

