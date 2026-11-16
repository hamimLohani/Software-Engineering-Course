// URL of our JSON Server
const API_URL = "http://localhost:3000/students";

// Pagination state
let currentPage = 1;
const limit = 4; // 4 students per page

// DOM Elements
const studentForm = document.getElementById("student-form");
const studentIdInput = document.getElementById("student-id");
const nameInput = document.getElementById("name");
const emailInput = document.getElementById("email");
const ageInput = document.getElementById("age");
const departmentInput = document.getElementById("department");
const statusInput = document.getElementById("status");
const formTitle = document.getElementById("form-title");
const modeBadge = document.getElementById("mode-badge");
const cancelBtn = document.getElementById("cancel-btn");
const tableBody = document.getElementById("student-table-body");
const prevBtn = document.getElementById("prev-btn");
const nextBtn = document.getElementById("next-btn");
const pageInfo = document.getElementById("page-info");

// Filter and Sort Elements
const filterDept = document.getElementById("filter-dept");
const filterStatus = document.getElementById("filter-status");
const sortField = document.getElementById("sort-field");
const sortOrder = document.getElementById("sort-order");

// ------------------------------------------------------------------
// 1. READ / GET (Load students with pagination, sorting & filtering)
// ------------------------------------------------------------------
function loadStudents() {
  // Build query string for JSON Server
  let url = `${API_URL}?_page=${currentPage}&_limit=${limit}`;

  // Add department filter if selected
  if (filterDept.value) {
    url += `&department=${encodeURIComponent(filterDept.value)}`;
  }

  // Add status filter if selected
  if (filterStatus.value) {
    url += `&status=${encodeURIComponent(filterStatus.value)}`;
  }

  // Add sorting
  url += `&_sort=${sortField.value}&_order=${sortOrder.value}`;

  // Execute GET request
  fetch(url)
    .then(function(response) {
      // json-server returns total items count in 'x-total-count' header
      const totalCount = response.headers.get("x-total-count");
      updatePaginationControls(totalCount);
      return response.json();
    })
    .then(function(students) {
      displayStudents(students);
    })
    .catch(function(error) {
      console.error("Error loading students:", error);
    });
}

// Render student table rows
function displayStudents(students) {
  tableBody.innerHTML = "";

  if (students.length === 0) {
    tableBody.innerHTML = `<tr><td colspan="7" class="empty-state">No students found matching current filters.</td></tr>`;
    return;
  }

  students.forEach(function(student) {
    const row = document.createElement("tr");

    const statusBadgeClass = student.status === "Active" ? "status-active" : "status-inactive";

    row.innerHTML = `
      <td><strong>#${student.id}</strong></td>
      <td><strong>${student.name}</strong></td>
      <td style="color: var(--text-muted);">${student.email}</td>
      <td>${student.age}</td>
      <td>${student.department}</td>
      <td><span class="status-badge ${statusBadgeClass}">${student.status}</span></td>
      <td>
        <div class="actions-cell">
          <button class="btn btn-edit btn-small" onclick="startEdit('${student.id}')" title="Full Update (PUT)">✏️ Edit</button>
          <button class="btn btn-toggle btn-small" onclick="toggleStatus('${student.id}', '${student.status}')" title="Partial Update (PATCH)">🔄 Toggle</button>
          <button class="btn btn-delete btn-small" onclick="deleteStudent('${student.id}')" title="Remove (DELETE)">🗑️ Delete</button>
        </div>
      </td>
    `;
    tableBody.appendChild(row);
  });
}

// Update pagination buttons and label
function updatePaginationControls(totalCount) {
  pageInfo.textContent = `Page ${currentPage}`;
  
  // Previous button disable check
  prevBtn.disabled = currentPage <= 1;

  // Next button disable check if total count exists
  if (totalCount !== null) {
    const totalPages = Math.ceil(totalCount / limit);
    pageInfo.textContent = `Page ${currentPage} of ${totalPages || 1}`;
    nextBtn.disabled = currentPage >= totalPages;
  }
}

// ------------------------------------------------------------------
// 2. CREATE (POST) & FULL UPDATE (PUT)
// ------------------------------------------------------------------
studentForm.addEventListener("submit", function(event) {
  event.preventDefault();

  const id = studentIdInput.value;
  const studentData = {
    name: nameInput.value,
    email: emailInput.value,
    age: parseInt(ageInput.value),
    department: departmentInput.value,
    status: statusInput.value
  };

  if (id) {
    // If ID exists, do PUT request (update full object)
    fetch(`${API_URL}/${id}`, {
      method: "PUT",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(studentData)
    })
    .then(function(response) { return response.json(); })
    .then(function() {
      resetForm();
      loadStudents();
    })
    .catch(function(error) { console.error("Error updating student:", error); });
  } else {
    // If no ID, do POST request (create new student)
    fetch(API_URL, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(studentData)
    })
    .then(function(response) { return response.json(); })
    .then(function() {
      resetForm();
      loadStudents();
    })
    .catch(function(error) { console.error("Error adding student:", error); });
  }
});

// Populate form for editing
function startEdit(id) {
  fetch(`${API_URL}/${id}`)
    .then(function(response) { return response.json(); })
    .then(function(student) {
      studentIdInput.value = student.id;
      nameInput.value = student.name;
      emailInput.value = student.email;
      ageInput.value = student.age;
      departmentInput.value = student.department;
      statusInput.value = student.status;

      formTitle.innerHTML = `<span class="icon">✏️</span> Edit Student (ID: ${student.id})`;
      if (modeBadge) {
        modeBadge.textContent = "PUT Mode";
        modeBadge.style.background = "var(--warning-light)";
        modeBadge.style.color = "var(--warning-text)";
      }
      cancelBtn.style.display = "inline-flex";
      window.scrollTo({ top: 0, behavior: "smooth" });
    });
}

// Cancel edit mode
cancelBtn.addEventListener("click", resetForm);

function resetForm() {
  studentForm.reset();
  studentIdInput.value = "";
  formTitle.innerHTML = `<span class="icon">➕</span> Add New Student`;
  if (modeBadge) {
    modeBadge.textContent = "POST Mode";
    modeBadge.style.background = "var(--primary-light)";
    modeBadge.style.color = "var(--primary)";
  }
  cancelBtn.style.display = "none";
}

// ------------------------------------------------------------------
// 3. PARTIAL UPDATE (PATCH)
// ------------------------------------------------------------------
function toggleStatus(id, currentStatus) {
  const newStatus = currentStatus === "Active" ? "Inactive" : "Active";

  // PATCH modifies only the specified field ('status')
  fetch(`${API_URL}/${id}`, {
    method: "PATCH",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ status: newStatus })
  })
  .then(function(response) { return response.json(); })
  .then(function() {
    loadStudents();
  })
  .catch(function(error) { console.error("Error patching student:", error); });
}

// ------------------------------------------------------------------
// 4. DELETE (DELETE)
// ------------------------------------------------------------------
function deleteStudent(id) {
  if (confirm("Are you sure you want to delete this student?")) {
    fetch(`${API_URL}/${id}`, {
      method: "DELETE"
    })
    .then(function(response) { return response.json(); })
    .then(function() {
      loadStudents();
    })
    .catch(function(error) { console.error("Error deleting student:", error); });
  }
}

// ------------------------------------------------------------------
// 5. EVENT LISTENERS FOR PAGINATION, FILTER & SORT
// ------------------------------------------------------------------
prevBtn.addEventListener("click", function() {
  if (currentPage > 1) {
    currentPage--;
    loadStudents();
  }
});

nextBtn.addEventListener("click", function() {
  currentPage++;
  loadStudents();
});

filterDept.addEventListener("change", function() {
  currentPage = 1;
  loadStudents();
});

filterStatus.addEventListener("change", function() {
  currentPage = 1;
  loadStudents();
});

sortField.addEventListener("change", function() {
  loadStudents();
});

sortOrder.addEventListener("change", function() {
  loadStudents();
});

// Initial load
loadStudents();
