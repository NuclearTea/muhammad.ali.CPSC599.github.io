// Function to load text file and display its content
async function loadCode() {
  try {
    const response = await fetch(
      "assets/Assignment 4/Code/PaintingMyWorkout.ino",
    );

    const code = await response.text();
    const codeContainer = document.getElementById("code-container");
    codeContainer.textContent = code;
    codeContainer.style.display = "block";

    // Re-apply Prism highlighting after adding the code
    Prism.highlightElement(codeContainer);
  } catch (error) {
    console.error("Error loading the file:", error);
  }
}

// Call the function to load the code when the page loads
window.onload = loadCode;

