import { Routes } from '@angular/router';
import { AddItemComponent } from './add-item/add-item.component';
import { EditItemComponent } from './edit-item/edit-item.component';
import { HomeComponent } from './home/home.component';

export const routes: Routes = [
  { path: '', component: HomeComponent },
  { path: 'add', component: AddItemComponent },
  { path: 'edit/:id', component: EditItemComponent },
];
