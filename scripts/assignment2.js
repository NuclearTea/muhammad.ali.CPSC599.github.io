// Function to load text file and display its content
async function loadCode() {
  try {
    const response = await fetch(
      "assets/Assignment 2/Code/Copper_wire_capacitive_sensing/Copper_wire_capacitive_sensing.ino"
    ); // Replace with the path to your text file
    const code = await response.text();
    const codeContainer = document.getElementById("code-container");
    codeContainer.textContent = code;

    // Re-apply Prism highlighting after adding the code
    Prism.highlightElement(codeContainer);
  } catch (error) {
    console.error("Error loading the file:", error);
  }
}

// Call the function to load the code when the page loads
window.onload = loadCode;
