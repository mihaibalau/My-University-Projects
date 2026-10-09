import { Component } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-add-item',
  standalone: true,
  templateUrl: './add-item.component.html',
  styleUrls: ['./add-item.component.css'],
  imports: []
})

export class AddItemComponent {
  document = {
    author: '',
    title: '',
    noPages: 0,
    type: ''
  };

  responseMessage: string = '';

  constructor(private http: HttpClient) {}

  onSubmit(event: Event) {
    event.preventDefault();

    if (
      !this.document.author ||
      !this.document.title ||
      !this.document.noPages ||
      !this.document.type
    ) {
      this.responseMessage = "Please fill in all fields.";
      return;
    }

    this.http.post<any>('http://localhost/Lab7/add_doc.php', this.document)
      .subscribe({
        next: (response) => {
          this.responseMessage = response.success
            ? "Document added successfully!"
            : "Failed to add document.";
        },
        error: () => {
          this.responseMessage = "Error connecting to the server.";
        }
      });
  }
}
