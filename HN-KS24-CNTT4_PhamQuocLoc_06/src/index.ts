class Audience {
    static upId = 1;
    id: number
    name: string
    email: string
    phone: string
    constructor(name: string, email: string, phone: string) {
        this.id = Audience.upId++
        this.name = name
        this.email = email
        this.phone = phone
    }
    getDetails(): string {
        return `Id:${this.id}, Name: ${this.name}, Email: ${this.email}, Phone: ${this.phone}`
    }
}

abstract class Movie {
    static upId = 1;
    id: number
    title: string
    genre: string
    ticketPrice: number
    isShowing: boolean
    constructor(title: string, genre: string, ticketPrice: number, isShowing: boolean) {
        this.id = Movie.upId++
        this.title = title
        this.genre = genre
        this.ticketPrice = ticketPrice
        this.isShowing = isShowing
    }
    startShow() {
        return this.isShowing = true
    }
    stopShow() {
        return this.isShowing = false
    }
    abstract calculateTicketCost(quantity: number): number;
    abstract getSpecialOffers(): string[];
    abstract getMovieInfo(): string;
    getDetails() {
        return `Id:${this.id}, Title: ${this.title}, Genre: ${this.genre}, Price: ${this.ticketPrice}`
    }
}

class ActionMovie extends Movie {
    constructor(title: string, genre: string, ticketPrice: number, isShowing: boolean) {
        super(title, genre, ticketPrice, isShowing)
    }
    calculateTicketCost(quantity: number) {
        return this.ticketPrice * quantity;
    }
    getSpecialOffers() {
        return [`Miễn phí bắp rang`, `Tặng poster`];
    }
    getMovieInfo() {
        return `Phim hành động gay cấn, kỹ xảo hoành tráng`
    }

}

class ComedyMovie extends Movie {
    constructor(title: string, genre: string, ticketPrice: number, isShowing: boolean) {
        super(title, genre, ticketPrice, isShowing)
    }
    calculateTicketCost(quantity: number) {
        return this.ticketPrice * quantity;
    }
    getSpecialOffers() {
        return [`Giảm 10% cho nhóm trên 4 người`];
    }
    getMovieInfo() {
        return `Phim hành động gay cấn, kỹ xảo hoành tráng`
    }

}

class AnimationMovie extends Movie {
    constructor(title: string, genre: string, ticketPrice: number, isShowing: boolean) {
        super(title, genre, ticketPrice, isShowing)
    }
    calculateTicketCost(quantity: number) {
        return this.ticketPrice * quantity;
    }
    getSpecialOffers() {
        return [`Giảm giá cho trẻ em dưới 12 tuổi`];
    }
    getMovieInfo() {
        return `Phim hành động gay cấn, kỹ xảo hoành tráng`
    }

}

class TicketBooking {
    static upId = 1
    bookingId: number
    audience: Audience
    movie: Movie
    quantity: number
    totalPrice: number
    constructor(audience: Audience, movie: Movie, quantity: number, totalPrice: number) {
        this.bookingId = TicketBooking.upId++
        this.audience = audience
        this.movie = movie
        this.quantity = quantity
        this.totalPrice = totalPrice
    }
    getDetails() {
        return `Id:${this.bookingId}, Audience: ${this.audience.name}, Movie: ${this.movie.title}, Quantity: ${this.quantity},Price: ${this.totalPrice}`
    }
}

class Cinema {
    movies: Movie[]
    audiences: Audience[]
    bookings: TicketBooking[]
    addMovie(movie: Movie): void {
        this.movies.push(movie);
    }
    addAudience(name: string, email: string, phone: string): Audience {
        const newAudience = new Audience(name, email, phone);
        this.audiences.push(newAudience);
        console.log(`Thêm khán giả thành công`);
        return newAudience;
    }

    bookTickets(audienceId: number, movieId: number, quantity: number): TicketBooking | null {
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
    cancelMovie(movieId: number): void {
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
    listShowingMovies(): void {
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