import { Component } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { RouterLink, RouterLinkActive } from '@angular/router';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [CommonModule, RouterOutlet, RouterLink, RouterLinkActive],
  template: `
    <div class="app-container">
      <header>
        <h1>Documents Manager</h1>
        <nav>
          <a routerLink="/" routerLinkActive="active-link" [routerLinkActiveOptions]="{ exact: true }">Home</a>
          <a routerLink="/add" routerLinkActive="active-link">Add Document</a>
        </nav>
      </header>

      <main>
        <router-outlet />
      </main>
    </div>
  `,
  styles: [`
    .app-container {
      font-family: Arial, sans-serif;
      text-align: center;
      padding: 2rem;
    }

    header h1 {
      font-size: 3rem;
      margin-bottom: 1rem;
      color: #333;
    }

    nav {
      margin-bottom: 2rem;
    }

    nav a {
      margin: 0 1rem;
      text-decoration: none;
      font-size: 1.1rem;
      color: #0077cc;
      padding: 0.5rem 1rem;
      border-radius: 5px;
      transition: background-color 0.3s;
    }

    nav a:hover {
      background-color: #e6f2ff;
    }

    .active-link {
      font-weight: bold;
      border-bottom: 2px solid #0077cc;
    }

    main {
      margin-top: 1rem;
    }
  `]
})
export class AppComponent {
  title = 'documents-app';
}
