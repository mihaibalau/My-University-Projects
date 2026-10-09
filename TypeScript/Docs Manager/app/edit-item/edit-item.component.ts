import { Component } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { HttpClient, HttpParams, HttpHeaders } from '@angular/common/http';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-edit-item',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './edit-item.component.html',
  styleUrls: ['./edit-item.component.css']
})
export class EditItemComponent {
  document: any = { author: '', title: '', noPages: 0, type: '' };
  id!: number;
  responseMessage = '';

  constructor(
    private route: ActivatedRoute,
    private http: HttpClient,
    private router: Router
  ) {
    this.id = +this.route.snapshot.paramMap.get('id')!;
    this.loadDocument();
  }

  private loadDocument() {
    this.http.get<any>(`http://localhost/Lab7/get_doc_by_id.php?id=${this.id}`)
      .subscribe({
        next: (doc) => this.document = {
          ...doc,
          noPages: Number(doc.noPages)
        },
        error: () => this.responseMessage = 'Failed to load document.'
      });
  }

  onSubmit(event: Event) {
    event.preventDefault();

    const body = new HttpParams()
      .set('id', this.id.toString())
      .set('author', this.document.author)
      .set('title', this.document.title)
      .set('noPages', this.document.noPages.toString())
      .set('type', this.document.type);

    const headers = new HttpHeaders({
      'Content-Type': 'application/x-www-form-urlencoded'
    });

    this.http.post('http://localhost/Lab7/update_doc.php', body.toString(), { 
      headers, 
      responseType: 'text' 
    }).subscribe({
      next: (responseText) => this.handleResponse(responseText),
      error: (error) => this.handleError(error)
    });
  }

  private handleResponse(responseText: string) {
    console.log('Server Response:', responseText);
    
    if (responseText.includes("Failed")) {
      this.responseMessage = "Failed to update document. Server error.";
    } else {
      this.responseMessage = "Document updated successfully!";
      setTimeout(() => this.router.navigate(['/']), 1000);
    }
  }

  private handleError(error: any) {
    console.error('Request Error:', error);
    this.responseMessage = error.status === 0 
      ? "Could not connect to server." 
      : "Unexpected error occurred.";
  }
}
