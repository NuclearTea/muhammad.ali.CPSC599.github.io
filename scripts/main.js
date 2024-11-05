const movableText = document.getElementById("Moveable-Text");
const container = document.getElementById("Lightsabre-Piano");

let lastY = 0;

if (!movableText || !container) {
  console.error("Element not found", movableText, container, hiddenLink);
} else {
  document.addEventListener("mousemove", (event) => {
    const containerRect = container.getBoundingClientRect();
    const boxRect = movableText.getBoundingClientRect();

    // Calculate the distance from the cursor to the top of the box
    const cursorY = event.clientY;
    const boxBottomY = boxRect.bottom;

    const isMovingUp = cursorY <= lastY;

    // If cursor is approaching from below and within the container
    if (isMovingUp && cursorY > boxBottomY && cursorY < containerRect.bottom) {
      const distance = cursorY - boxBottomY;

      const maxPushUpPxls = 125;
      // Push the box up based on how close the cursor is
      const pushUp = Math.max(0, maxPushUpPxls - distance); // 100 is the max push distance
      movableText.style.transform = `translateY(-${pushUp}px)`;

      if (pushUp >= maxPushUpPxls * 0.95) {
        window.location.assign("LightsabrePiano.html");
      }
    } else {
      // Reset the box to its original position if the cursor is not below
      movableText.style.transform = `translateY(0px)`;
    }

    lastY = cursorY; // Update the last Y position
  });
}
