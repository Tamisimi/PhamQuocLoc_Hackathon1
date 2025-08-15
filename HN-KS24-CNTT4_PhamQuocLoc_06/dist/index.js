class Audience {
    constructor(name, email, phone) {
        this.id = Audience.upId++;
        this.name = name;
        this.email = email;
        this.phone = phone;
    }
    getDetails() {
        return `Id:${this.id}, Name: ${this.name}, Email: ${this.email}, Phone: ${this.phone}`;
    }
}
Audience.upId = 1;
class Movie {
    constructor(title, genre, ticketPrice, isShowing) {
        this.id = Movie.upId++;
        this.title = title;
        this.genre = genre;
        this.ticketPrice = ticketPrice;
        this.isShowing = isShowing;
    }
    startShow() {
        return this.isShowing = true;
    }
    stopShow() {
        return this.isShowing = false;
    }
    getDetails() {
        return `Id:${this.id}, Title: ${this.title}, Genre: ${this.genre}, Price: ${this.ticketPrice}`;
    }
}
Movie.upId = 1;
class ActionMovie extends Movie {
    constructor(title, genre, ticketPrice, isShowing) {
        super(title, genre, ticketPrice, isShowing);
    }
    calculateTicketCost(quantity) {
        return this.ticketPrice * quantity;
    }
    getSpecialOffers() {
        return [`Miễn phí bắp rang`, `Tặng poster`];
    }
    getMovieInfo() {
        return `Phim hành động gay cấn, kỹ xảo hoành tráng`;
    }
}
class ComedyMovie extends Movie {
    constructor(title, genre, ticketPrice, isShowing) {
        super(title, genre, ticketPrice, isShowing);
    }
    calculateTicketCost(quantity) {
        return this.ticketPrice * quantity;
    }
    getSpecialOffers() {
        return [`Giảm 10% cho nhóm trên 4 người`];
    }
    getMovieInfo() {
        return `Phim hành động gay cấn, kỹ xảo hoành tráng`;
    }
}
class AnimationMovie extends Movie {
    constructor(title, genre, ticketPrice, isShowing) {
        super(title, genre, ticketPrice, isShowing);
    }
    calculateTicketCost(quantity) {
        return this.ticketPrice * quantity;
    }
    getSpecialOffers() {
        return [`Giảm giá cho trẻ em dưới 12 tuổi`];
    }
    getMovieInfo() {
        return `Phim hành động gay cấn, kỹ xảo hoành tráng`;
    }
}
class TicketBooking {
    constructor(audience, movie, quantity, totalPrice) {
        this.bookingId = TicketBooking.upId++;
        this.audience = audience;
        this.movie = movie;
        this.quantity = quantity;
        this.totalPrice = totalPrice;
    }
    getDetails() {
        return `Id:${this.bookingId}, Audience: ${this.audience.name}, Movie: ${this.movie.title}, Quantity: ${this.quantity},Price: ${this.totalPrice}`;
    }
}
TicketBooking.upId = 1;
class Cinema {
    addMovie(movie) {
        this.movies.push(movie);
    }
    addAudience(name, email, phone) {
        const newAudience = new Audience(name, email, phone);
        this.audiences.push(newAudience);
        console.log(`Thêm khán giả thành công`);
        return newAudience;
    }
    bookTickets(audienceId, movieId, quantity) {
        const audience = this.audiences.find(a => a.id === audienceId);
        if (!audience) {
            console.log("Không tìm thấy khán giả.");
            return null;
        }
        const movie = this.movies.find(m => m.id === movieId);
        if (!movie) {
            console.log("Không tìm thấy phim.");
            return null;
        }
        if (!movie.isShowing) {
            console.log("Phim đã ngừng chiếu.");
            return null;
        }
        const total = movie.calculateTicketCost(quantity);
        const booking = new TicketBooking(audience, movie, quantity, total);
        this.bookings.push(booking);
        console.log(`Đặt vé thành công: ${booking.getDetails()}`);
        return booking;
    }
    cancelMovie(movieId) {
        const movie = this.movies.find(m => m.id === movieId);
        if (!movie) {
            console.log("Không tìm thấy phim để ngừng chiếu.");
            return;
        }
        if (!movie.isShowing) {
            console.log("Phim đã ngừng chiếu.");
            return;
        }
        movie.stopShow();
        console.log(` Đã ngừng chiếu:`);
    }
    listShowingMovies() {
        const showing = this.movies.filter(m => m.isShowing);
        if (showing.length === 0) {
            console.log("không có phim nào đang chiếu.");
            return;
        }
        const lines = showing.map(m => `- ${m.id} | ${m.title} | ${m.genre} | ${m.ticketPrice} VND`);
        console.log("Danh sách phim đang chiếu:");
        lines.forEach(l => console.log(lines));
    }
}
const cinema = new Cinema();
const a1 = cinema.addAudience("Nguyen Van A", "a@example.com", "0900000001");
const a2 = cinema.addAudience("Tran Thi B", "b@example.com", "0900000002");
const m1 = new ActionMovie("Fast & Furious X", "Hành động", 90000, true);
const m2 = new ComedyMovie("Hài Việt 2025", "Hài hước", 80000, true);
const m3 = new AnimationMovie("Pixie Adventures", "Hoạt hình", 70000, false);
cinema.addMovie(m1);
cinema.addMovie(m2);
cinema.addMovie(m3);
cinema.listShowingMovies();
cinema.bookTickets(a1.id, m2.id, 2);
cinema.bookTickets(a2.id, m2.id, 5);
cinema.cancelMovie(m1.id);
cinema.listShowingMovies();
