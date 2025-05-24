#include <iostream>
#include <memory>
#include <sqlite3.h>
#include <stdexcept>
#include <string>

#include <sqlite_orm/sqlite_orm.h>

struct User {
    int id;
    std::string firstName;
    std::string lastName;
    int birthDate;
    std::unique_ptr<std::string> imageUrl;
    int typeId;
};

struct UserType {
    int id;
    std::string name;
};

int main()
{
    // Build connection and connect
    using namespace sqlite_orm;
    auto storage = make_storage(
        "./waveguide/snapshot/snapshot/data/snapshot.db",
        make_table(
            "users",
            make_column("id", &User::id, primary_key().autoincrement()),
            make_column("first_name", &User::firstName),
            make_column("last_name", &User::lastName),
            make_column("birth_date", &User::birthDate),
            make_column("image_url", &User::imageUrl),
            make_column("type_id", &User::typeId)
        ),
        make_table("user_types", make_column("id", &UserType::id, primary_key().autoincrement()), make_column("name", &UserType::name, default_value("name_placeholder")))
    );
    storage.sync_schema();
    storage.remove_all<User>();

    User user{ -1, "Jonh", "Doe", 664416000, std::make_unique<std::string>("url_to_heaven"), 3 };

    auto insertedId = storage.insert(user);
    std::cout << "insertedId = " << insertedId << std::endl; //  insertedId = 8
    user.id = insertedId;

    User secondUser{ -1, "Alice", "Inwonder", 831168000, {}, 2 };
    insertedId    = storage.insert(secondUser);
    secondUser.id = insertedId;

    try {
        auto user = storage.get<User>(insertedId);
        std::cout << "user = " << user.firstName << " " << user.lastName << std::endl;
    }
    catch (std::system_error e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "unknown exeption" << std::endl;
    }

    if (auto user = storage.get_pointer<User>(insertedId)) {
        std::cout << "user = " << user->firstName << " " << user->lastName << std::endl;
    }
    else {
        std::cout << "no user with id " << insertedId << std::endl;
    }

    user.firstName = "Nicholas";
    user.imageUrl =
        std::make_unique<std::string>("https://cdn1.iconfinder.com/data/icons/man-icon-set/100/man_icon-21-512.png");
    storage.update(user);

    storage.update_all(set(c(&User::lastName) = "Hardey", c(&User::typeId) = 2), where(c(&User::firstName) == "Tom"));

    storage.remove<User>(insertedId);

    auto allUsers = storage.get_all<User>();

    std::cout << "allUsers (" << allUsers.size() << "):" << std::endl;
    for (auto& user : allUsers) {
        std::cout
            << storage.dump(user)
            << std::endl; //  dump returns std::string with json-like style object info. For example: { id : '1', first_name
                          //  : 'Jonh', last_name : 'Doe', birth_date : '664416000', image_url :
                          //  'https://cdn1.iconfinder.com/data/icons/man-icon-set/100/man_icon-21-512.png', type_id : '3' }
    }

    auto allUsersList = storage.get_all<User, std::list<User>>();

    for (auto& user : storage.iterate<User>()) {
        std::cout << storage.dump(user) << std::endl;
    }

    return 0;
}