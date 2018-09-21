#include <iostream>
#include <vector>

// Assume these already exist.

struct Song {
    std::string name;
    int duration;
};

class Album {
    std::string title;
    std::vector<std::string> artists;
    std::vector<Song> songs;
public:
    Album(const std::vector<std::string> &artists,
           const std::vector<Song> &songs)
            : artists{artists}, songs{songs} {}

    const std::string &get_title() const {
        return title;
    }
    const std::vector<std::string> &get_artists() const {
        return artists;
    }
    const std::vector<Song> &get_songs() const {
        return songs;
    }
};

class Book {
    std::string title;
    std::vector<std::string> authors;
    std::string blurb;
    std::vector<std::string> contents; // Pages.
public:
    Book(const std::vector<std::string> &authors,
         const std::string &blurb)
         : authors{authors}, blurb{blurb} {}

    const std::string &get_title() const {
        return title;
    }
    const std::vector<std::string> &get_authors() const {
        return authors;
    }
    const std::string &get_blurb() const {
        return blurb;
    }
    const std::vector<std::string> &get_contents() const {
        return contents;
    }
};

// Assume a common interface was needed, after a while, to connect the above classes.
// Can use adapter design pattern.

class MediaResource {
public:
    virtual std::string get_name() const = 0;
    virtual std::vector<std::string> get_creators() const = 0;
    virtual std::string get_summary() const = 0;
    virtual int get_length() const = 0;
};

class AlbumToMediaResourceAdapter : public MediaResource {
    const Album &album; // Doesn't have to be const.
public:
    AlbumToMediaResourceAdapter(const Album &album)
        : album{album} {}

    std::string get_name() const {
        return album.get_title();
    }
    std::vector<std::string> get_creators() const override {
        return album.get_artists();
    }
    std::string get_summary() const override {
        std::string summary;
        for(const auto &song : album.get_songs()) {
            summary += song.name + " ";
        }
        return summary;
    }
    int get_length() const override {
        return album.get_songs().size();
    }
};

class BookToMediaResourceAdapter : public MediaResource {
    const Book &book;
public:
    BookToMediaResourceAdapter(const Book &book)
        : book{book} {}

    std::string get_name() const override {
        return book.get_title();
    }
    std::vector<std::string> get_creators() const override {
        return book.get_authors();
    }
    std::string get_summary() const override {
        return book.get_blurb();
    }
    int get_length() const override {
        return book.get_contents().size();
    }
};

// End pattern.

std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &rhs) {
    for(const auto &string : rhs) {
        os << string << " ";
    }
    return os;
}

// Can process any type of resource.
void print_media_details(const MediaResource &resource) {
    std::cout << "Resource name: " << resource.get_name() << std::endl
              << "Creators: " << resource.get_creators() << std::endl
              << "Summary: " << resource.get_summary() << std::endl
              << "Length: " << resource.get_length();
}

int main() {

    return 0;
}

/*
Challenge: Use adapter design pattern.
struct Square {
    int side{};

    explicit Square(int side)
        : side(side) {
    }
};

struct Rectangle {
    virtual int width() const = 0;
    virtual int height() const = 0;

    int area() const {
        return width() * height();
    }
};

struct SquareToRectangleAdapter : Rectangle {
    Square square;

    SquareToRectangleAdapter(const Square &square)
        : square{square} {}

    int width() const override {
        return square.side;
    }
    int height() const override {
        return square.side;
    }
};
 */