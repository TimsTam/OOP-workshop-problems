#include <iostream>
#include <vector>
#include <string>

using namespace std;

class MediaItem {
    private:
        string title;
        int releaseYear;
    public:
        MediaItem(const string& t = "", const int& y = 0) : title(t), releaseYear(y) {}
        virtual void display() const = 0;
        friend ostream& operator<<(ostream& out, const MediaItem& mem);
};

ostream& operator<<(ostream& out, const MediaItem& mem) {
    out << "title: " << mem.title << " releaseYear: " << mem.releaseYear;
    return out;
}

class Book : public MediaItem {
    private:
        string author;
        int pageCount;
    public:
        Book(const string& t = "", const int& y = 0, const string& a = "", const int& p = 0) : MediaItem(t, y), author(a), pageCount(p) {}
        virtual void display() const override;
};

void Book::display() const {
    cout << "Book: " << *this << " Pages: " << pageCount << endl;
}

class DigitalCopy {
    public:
        virtual void showDownloadDetails() const = 0;
};

class MusicAlbum : public MediaItem {
    private:
        string artist;
        int trackCount;
    public:
        MusicAlbum(const string& t = "", const int& y = 0, const string& a = "", const int& tc = 0) : MediaItem(t, y), artist(a), trackCount(tc) {}
        virtual void display() const override;
        virtual void showDownloadDetails() const;
};

void MusicAlbum::showDownloadDetails() const {
    cout << "Music album download details: [URL]" << endl;
}

void MusicAlbum::display() const {
    cout << "Music Album: " << *this << " Tracks: " << trackCount << endl;
}

class Movie : public MediaItem {
    private:
        string director;
        int duration;
    public:
        Movie(const string& t = "", const int& y = 0, const string& d = "", const int& dur = 0) : MediaItem(t, y), director(d), duration(dur) {}
        virtual void display() const override;
        virtual void showDownloadDetails() const;
};

void Movie::showDownloadDetails() const {
    cout << "Download available at [URL]" << endl;
}

void Movie::display() const {
    cout << "Movie: " << *this << " Duration: " << duration << " mins" << endl;
}

int main() {
    vector<MediaItem *> items;
    items.push_back(new Book("1984", 1949, "George Orwell", 328));
    items.push_back(new Movie("Inception", 2010, "Christopher Nolan", 148));
    items.push_back(new MusicAlbum("Thriller", 1982, "Michael Jackson", 9));

    int idx = 1;
    for (auto item : items)
    {
        cout << "Task " << idx++ << ": ";
        item->display();

        DigitalCopy *digital = dynamic_cast<DigitalCopy *>(item);
        if (digital)
        {
            cout << "Task " << idx++ << ": ";
            digital->showDownloadDetails();
        }
    }
    for (auto item : items)
        delete item;

    items.clear();

    return 0;
}
