# option_pricing.R
library(tidyverse)
library(ggplot2)

install.packages("C:\\Users\\sanaa\\Documents\\C++ HW\\GH2\\MCOptionPricing_0.1.0.tar.gz",
                 type = "source",
                 repos = NULL)
# load to memory
library("MCOptionPricing")

# Function to call the C++ function with different seeds
price_option <- function(seed, use_antithetic) {
  set.seed(seed)
  Expiry <- 1
  Strike <- 120
  Spot <- 105
  Vol <- 0.2
  r <- 0.05
  NumberOfPaths <- 1000
  alpha <- 0.05
  optionType <- 'c' # 'c' for call, 'p' for put

  price_option(Expiry, Strike, Spot, Vol, r, NumberOfPaths, alpha, optionType, use_antithetic)
}

# Call the function 1000 times without antithetic variates
results_without_antithetic <- numeric(1000)
for (i in 1:1000) {
  results_without_antithetic[i] <- price_option(i, FALSE)
}

# Compute the mean and standard deviation
mean_without_antithetic <- mean(results_without_antithetic)
sd_without_antithetic <- sd(results_without_antithetic)

# Call the function 1000 times with antithetic variates
results_with_antithetic <- numeric(1000)
for (i in 1:1000) {
  results_with_antithetic[i] <- price_option(i, TRUE)
}

# Compute the mean and standard deviation
mean_with_antithetic <- mean(results_with_antithetic)
sd_with_antithetic <- sd(results_with_antithetic)

# Create a visualization of the distribution densities
if (!require("ggplot2")) {
  install.packages("ggplot2")
}
library(ggplot2)
data <- data.frame(
  value = c(results_without_antithetic, results_with_antithetic),
  type = rep(c("Without Antithetic", "With Antithetic"), each = 1000)
)

ggplot(data, aes(x = value, fill = type)) +
  geom_density(alpha = 0.5) +
  labs(title = "Distribution of Option Price Approximations",
       x = "Option Price",
       y = "Density",
       fill = "Method")

# Compare results and draw conclusions
cat("Mean without antithetic variates:", mean_without_antithetic, "\n")
cat("Standard deviation without antithetic variates:", sd_without_antithetic, "\n")
cat("Mean with antithetic variates:", mean_with_antithetic, "\n")
cat("Standard deviation with antithetic variates:", sd_with_antithetic, "\n")
