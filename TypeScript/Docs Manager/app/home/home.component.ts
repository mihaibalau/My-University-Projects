import { Component, effect, inject, signal } from '@angular/core';
import { CommonModule } from '@angular/common';
import { HttpClient } from '@angular/common/http';
import { ReactiveFormsModule, FormControl } from '@angular/forms';
import { Router, RouterModule } from '@angular/router';

@Component({
  selector: 'app-home',
  standalone: true,
  imports: [CommonModule, ReactiveFormsModule, RouterModule],
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css'],
})
export class HomeComponent {
  private http = inject(HttpClient);
  private router = inject(Router);

  types = ['All', 'Carte', 'Roman', 'Thriller', 'Poezie'];
  typeControl = new FormControl('All', { nonNullable: true });

  documents = signal<any[]>([]);

  constructor() {
    this.typeControl.valueChanges.subscribe(() => this.loadDocuments());
    this.loadDocuments();
  }

  loadDocuments() {
    const selectedType = this.typeControl.value;
    const query = selectedType !== 'All' ? `?type=${selectedType}` : '';

    this.http.get<any[]>(`http://localhost/Lab7/get_documents.php${query}`).subscribe({
      next: (docs) => this.documents.set(docs),
      error: (err) => console.error('Failed to fetch docs:', err),
    });
  }

  deleteDocument(id: number) {
    this.http.get(`http://localhost/Lab7/delete_doc.php?id=${id}`).subscribe({
      next: () => this.loadDocuments(),
      error: (err) => console.error('Failed to delete document:', err),
    });
  }

  editDocument(id: number) {
    this.router.navigate(['/edit', id]);
  }
}
