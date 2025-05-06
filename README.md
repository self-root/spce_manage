# SPCE Manage

**SPCE Manage** is a desktop application developed for SPCE (Service Port and the Coastal Environment), a company based in Toamasina, Madagascar. SPCE is responsible for collecting and managing garbage from commercial ships at the Port of Toamasina, in accordance with **MARPOL Annex V** – Garbage regulations.

This software was specifically designed to streamline and digitalize their ship waste processing workflow. It is not intended for general public use but is open-sourced as part of my professional portfolio to demonstrate my capabilities in desktop software development using **Qt, C++ and QML**.

## Features

### 🚢 Ship Information Management
- **Display Upcoming Ships:** Automatically lists ships scheduled to arrive at the Port of Toamasina.
- **Display Latest Arrivals:** View ships that have recently docked.
- **Search Functionality:** Easily locate ships by name or IMO number.

### 📄 Document Generation
Generates essential documents required for MARPOL compliance and operational processing:
- **Waste Delivery Certificate**  
  Follows *APPENDIX 3: Standard Format for the Waste Delivery Receipt*.
- **BSD (Bordereau de Suivi des Déchets Portuaires)**  
  A mandatory waste tracking document.
- **Invoice Generation**  
  Auto-generates invoice details per ship operation.

### 📊 Dashboard & Analytics
- **Real-time Stats:** Displays amount of garbage removed and total revenue.
- **Bar Chart:** Monthly revenue and waste collected trends.
- **Pie Chart:** Distribution of ship types.

### 🧾 Invoice Record Tracking
- View, and manage historical invoices.

## Technology Stack

- **C++ / Qt** – for core application logic and native performance.
- **QML** – for modern, fluid, and declarative UI design.
- **SQLite** – for lightweight, embedded local storage.

## Screenshots

| Home & Ship Schedule | Dashboard & Invoices | Ship search |
|----------|-----------|---------|
| ![Home & Ship Schedule Screenshot](https://github.com/self-root/spce_manage/blob/master/screenshots/spce_home.PNG) | ![Dashboard & Invoices Screenshot](https://github.com/self-root/spce_manage/blob/master/screenshots/spce_invoices.PNG) | ![Ship search Screenshot](https://github.com/self-root/spce_manage/blob/master/screenshots/spce_home_search.PNG) |

## About

This project was developed as a freelance contract for SPCE Madagascar. It is released publicly to showcase my skills in:
- Desktop software architecture
- UI/UX design with QML
- Working with real-world data and compliance documentation
- Building data visualization tools

Feel free to explore the code to see examples of structured Qt/C++ development and QML integration. If you're looking for a desktop software developer with experience in real-world industrial solutions, don’t hesitate to reach out.

---

